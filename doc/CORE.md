# CORE Documentation

## 1. Introduction

This document describes the Core game loop and framework architecture that manages the Arcade system. The Core class is the heart of the Arcade framework, responsible for:

- **Dynamic library loading** for games and displays
- **Game loop execution** and timing synchronization
- **Event handling** and input processing
- **Game switching** and menu navigation
- **Player management** and score persistence
- **Overlay rendering** (debug, leaderboard, menus)

The Core implements a sophisticated state machine that manages transitions between different games, menus, and display backends while maintaining consistent timing and responsiveness.

## 2. Core Architecture Overview

### 2.1 Core Class Structure

The Core class serves as the main orchestrator of the Arcade system:

```cpp
class Core {
public:
    Core();
    ~Core();
    
    int run();  // Main entry point
    
    // Game management
    std::string_view gameTitle(std::size_t index) const noexcept;
    void switchGame(std::size_t index);
    void setLeaderboardVisible(bool visible) noexcept;
    void toggleLeaderboardVisibility() noexcept;
    
    // Library management
    void loadLibrariesFromDirectory(std::string_view directory);
    
private:
    int game_loop();
    void applyPendingGameSwitch();
    // ... other private methods
};
```

### 2.2 Component Structure

The Core manages several key components:

```
┌─────────────────────────────────────────┐
│          Core Game Loop                 │
├─────────────────────────────────────────┤
│  • Current Game (IGame*)                │
│  • Current Display (IDisplay*)          │
│  • Player Manager (PlayerContainer)     │
│  • Available Games (vector)             │
│  • Available Displays (vector)          │
│  • Overlay System (Debug, Leaderboard)  │
│  • Menu System                          │
└─────────────────────────────────────────┘
```

## 3. Dynamic Library Management

### 3.1 Library Loading

The Core supports dynamic loading of games and display backends:

```cpp
void Core::loadLibrariesFromDirectory(std::string_view directory)
{
    // Scans directory for .so/.dll files
    // Attempts to load each as a game or display library
    // Extracts entry points (get_game() and get_display())
}
```

### 3.2 Entry Point Extraction

Libraries must export specific C functions:

```cpp
// For game libraries
extern "C" Arcade::IGame* get_game()
{
    return new Arcade::Snake();  // Or other game
}

// For display libraries
extern "C" Arcade::IDisplay* get_display()
{
    return new Arcade::SDL2();   // Or other display
}
```

The Core uses function pointers to access these entry points:

```cpp
using GameEntryPointFnc = IGame*(*)();
using DisplayEntryPointFnc = IDisplay*(*)();
```

### 3.3 Initial Library Selection

On startup, the Core selects initial libraries:

```cpp
void Core::selectInitialLibraries(
    std::string_view preferredDisplayPath,
    std::string_view preferredGamePath)
{
    // Load preferred libraries if specified
    // Otherwise use first available
}
```

## 4. Game Loop Execution

### 4.1 Main Game Loop

The `game_loop()` function is the core of the Arcade system:

```cpp
int Core::game_loop()
{
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    
    while (running) {
        // 1. Calculate delta time
        auto now = std::chrono::high_resolution_clock::now();
        auto deltaTime = now - lastFrameTime;
        lastFrameTime = now;
        
        // 2. Poll and handle events
        if (!pollCoreEvents()) {
            break;  // Exit requested
        }
        
        // 3. Update current game
        if (_currentGame) {
            _currentGame->update(deltaTime, _currentPlayer);
        }
        
        // 4. Clear and render display
        _currentDisplay->clear();
        
        // 5. Render game
        if (_currentGame) {
            _currentGame->render(*_currentDisplay);
        }
        
        // 6. Render overlays
        renderOverlays();
        
        // 7. Present frame
        _currentDisplay->refresh();
        
        // 8. Apply any pending game switches
        applyPendingGameSwitch();
    }
    
    return 0;  // Success
}
```

### 4.2 Delta Time Calculation

The Core measures elapsed time using high-resolution clock:

```cpp
auto now = std::chrono::high_resolution_clock::now();
auto deltaTime = now - lastFrameTime;
```

This delta time is passed to the game's `update()` method, enabling frame-rate independent gameplay.

### 4.3 Frame Pacing

The loop executes as fast as the display allows (typically ~60 FPS), with the game controlling its own movement speed using time accumulators.

## 5. Event Handling

### 5.1 Event Polling

The `pollCoreEvents()` function handles input and system events:

```cpp
bool Core::pollCoreEvents()
{
    while (auto event = _currentDisplay->pollEvent()) {
        // Handle display-specific events
        if (!_currentDisplay->isOpen()) {
            return false;  // Window closed
        }
        
        // Handle core-level events
        if (handleGlobalEvent(event)) {
            continue;  // Core handled it
        }
        
        // Pass to current game
        if (_currentGame) {
            _currentGame->handleEvent(event, *_currentDisplay);
        }
    }
    return true;  // Continue running
}
```

### 5.2 Global Event Handling

Certain events are handled at the Core level:

```cpp
bool Core::handleGlobalEvent(Arcade::Events::Event evt)
{
    switch (evt) {
        case ARC_KEY_ESCAPE:
            return quitGame();  // Exit the application
        
        case ARC_KEY_L:
            toggleLeaderboardVisibility();  // Show/hide leaderboard
            return true;
        
        case ARC_KEY_M:
            // Return to main menu
            queueGameSwitch(nullptr);
            return true;
        
        case ARC_KEY_N:
        case ARC_KEY_P:
            // Next/Previous game
            switchGame(nextIndex);
            return true;
        
        default:
            return false;  // Not a global event
    }
}
```

### 5.3 Event Flow

Event handling follows this hierarchy:
1. **Core Level**: Checks for global shortcuts (exit, menu, game switch)
2. **Game Level**: If not handled by Core, passes to current game
3. **Display Level**: The display backend updates its internal state

## 6. Game Switching

### 6.1 Deferred Game Switching

Game switches are queued and applied at safe points:

```cpp
void Core::queueGameSwitch(Arcade::IGame* nextGame)
{
    _pendingGameSwitch = nextGame;
    _shouldApplyGameSwitch = true;
}

void Core::applyPendingGameSwitch()
{
    if (!_shouldApplyGameSwitch)
        return;
    
    // Cleanup current game
    if (_currentGame) {
        _currentGame->destroy();
        delete _currentGame;
    }
    
    // Initialize new game
    _currentGame = _pendingGameSwitch;
    if (_currentGame) {
        _currentGame->init();
    }
    
    _shouldApplyGameSwitch = false;
}
```

This two-phase approach prevents issues where a game might be accessed while being destroyed.

### 6.2 Game Lifecycle

Each game follows a consistent lifecycle:

```
┌──────────┐
│ Load Game│
└────┬─────┘
     ↓
┌──────────┐
│  init()  │  ← Initialize game state
└────┬─────┘
     ↓
┌──────────────────┐
│  Game Loop       │
│ - update(dt)     │
│ - render()       │
│ - handleEvent()  │
└────┬─────────────┘
     ↓
┌──────────┐
│destroy() │  ← Clean up resources
└────┬─────┘
     ↓
┌───────────────┐
│ Unload Game   │
└───────────────┘
```

## 7. Player Management

### 7.1 Player Container

The Core manages players and their scores using PlayerContainer:

```cpp
class PlayerContainer {
public:
    void save(const std::filesystem::path& path);
    void load(const std::filesystem::path& path);
    
    Arcade::Player* findPlayerByName(std::string_view name);
    void addPlayer(const std::string& name);
    
    // ... other player management methods
};
```

### 7.2 Score Persistence

Player scores are saved to disk in a simple format:

```
playerName=score
john=1500
alice=2300
bob=450
```

The format allows easy parsing and modification.

### 7.3 Player-Game Association

During gameplay:
1. Player enters their name at the menu
2. Core finds or creates the player record
3. Game updates `player.score` during gameplay
4. When game ends, score is saved to disk

## 8. Display Management

### 8.1 Display Interface

All display backends inherit from IDisplay:

```cpp
class IDisplay {
public:
    virtual ~IDisplay() = default;
    
    virtual void clear() = 0;
    virtual void refresh() = 0;
    virtual void draw(const Shape& shape) = 0;
    virtual void draw(const Text& text) = 0;
    virtual bool isOpen() const = 0;
    virtual std::optional<Events::Event> pollEvent() = 0;
};
```

### 8.2 Display Switching

The Core can switch displays at runtime:

```cpp
// User requests display switch
_currentDisplay = _availableDisplays[newIndex];

// Current frame completes
// Next frame uses new display backend
```

Display switching is seamless because games render to an abstract interface.

### 8.3 Supported Displays

The framework supports multiple display backends:
- **SDL2**: 2D graphics with mouse/keyboard support
- **SFML**: Feature-rich graphics library
- **ncurses**: Terminal-based display for headless environments

## 9. Overlay System

### 9.1 Debug Overlay

The debug overlay provides real-time information:

```cpp
class DebugOverlay : public IGame {
    void render(IDisplay& display) override
    {
        // Display FPS counter
        // Show current player info
        // Display available games/displays
        // Show active game/display
    }
};
```

Toggled with a debug key or command-line flag.

### 9.2 Leaderboard Overlay

The leaderboard shows top scores:

```cpp
class LeaderboardOverlay : public IGame {
    void render(IDisplay& display) override
    {
        // Load and display top scores
        // Show player rankings
        // Display score for each game
    }
};
```

Toggled with a key (default: 'L') or menu selection.

### 9.3 Menu System

Multiple menu screens:

- **Main Menu**: Game/display selection
- **Username Menu**: Player name input
- **Pause Menu**: Game options
- **Game Over Menu**: Restart/menu options

## 10. Synchronization and Timing

### 10.1 Frame Synchronization

The Core synchronizes with the display:

```cpp
_currentDisplay->refresh();  // Wait for vsync
```

This ensures smooth frame presentation.

### 10.2 Delta Time Handling

Games receive accurate delta time:

```cpp
auto deltaTime = now - lastFrameTime;
_currentGame->update(deltaTime, _currentPlayer);
```

Games use this to implement frame-rate independent movement.

## 11. Error Handling and Cleanup

### 11.1 Resource Management

The Core ensures proper cleanup:

```cpp
~Core()
{
    if (_currentGame) {
        _currentGame->destroy();
        delete _currentGame;
    }
    
    if (_currentDisplay) {
        delete _currentDisplay;
    }
    
    // Close all loaded libraries
    for (auto& handle : _loadedLibraries) {
        closeLibrary(handle);
    }
}
```

### 11.2 Exception Handling

Library loading is protected:

```cpp
static SharedLibrary loadLibraryOrThrow(const char* path)
{
    auto handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        throw std::runtime_error(
            std::string("Failed to load library: ") + path
        );
    }
    return handle;
}
```

### 11.3 Graceful Shutdown

The Core shuts down gracefully:
1. Stops the game loop
2. Calls `destroy()` on current game
3. Closes all loaded libraries
4. Returns exit code

## 12. Key Design Patterns

### 12.1 Strategy Pattern

Display and game backends are strategies:
```cpp
std::unique_ptr<IDisplay> _currentDisplay;
std::unique_ptr<IGame> _currentGame;
```

Implementations can be swapped at runtime.

### 12.2 Observer Pattern

Games observe player input through events:
```cpp
game->handleEvent(event, display);
```

### 12.3 Factory Pattern

Library loading creates objects:
```cpp
auto gameFactory = (GameEntryPointFnc)dlsym(handle, "get_game");
_currentGame = gameFactory();
```

### 12.4 State Machine Pattern

The Core manages states:
```
Menu → Game → Menu
  ↓       ↓
Game1  Game2
```

## 13. Configuration and Initialization

### 13.1 Command-line Options

The Core can be configured via arguments:

```cpp
int main(int argc, char** argv)
{
    Core arcade;
    
    // Parse arguments
    // Set preferred game/display
    // Enable debug mode
    // etc.
    
    return arcade.run();
}
```

### 13.2 Library Paths

The Core searches for libraries in:
- `./lib/` (local libraries)
- System library paths
- Custom paths specified in config

## 14. Performance Considerations

### 14.1 Frame Rate Independence

All games run at the same frame rate through delta time:

```cpp
game->update(deltaTime, player);
```

Games manage their own internal timing.

### 14.2 Memory Efficiency

Dynamic allocation is minimized:
- Games are allocated/deallocated on switch
- Display backends are reused
- No unnecessary copies during rendering

### 14.3 Input Buffering

The Core polls all available events per frame:
```cpp
while (auto event = pollEvent()) {
    handleEvent(event);
}
```

This prevents input lag.

## 15. Conclusion

The Core class provides:

- **Robust framework** for managing games and displays
- **Flexible architecture** supporting dynamic library loading
- **Consistent lifecycle** for all games
- **Efficient event handling** and input processing
- **Frame-rate independent** gameplay through delta time
- **Persistent player management** with score saving
- **Overlay system** for debug and leaderboard info
- **Graceful error handling** and resource cleanup

This architecture enables:
- Adding new games without modifying Core
- Swapping display backends at runtime
- Consistent gameplay across different systems
- Easy extensibility with new features

The Core demonstrates best practices in game architecture: separation of concerns, dependency injection, and abstract interfaces that allow for flexible, maintainable code.
