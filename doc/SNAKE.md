# SNAKE Documentation

## 1. Introduction

This document describes the Snake game architecture and design patterns used to implement a classic Snake game within the Arcade framework.

The objectives of the Snake game are:

- The game area is a **60x30 cell grid** with wrapping enabled at edges
- The player controls a snake that grows in length as it eats apples
- Apples are randomly spawned on the map (maximum of 3 at any time)
- The game ends when the snake collides with itself
- Player earns 1 point for each apple eaten
- The game supports restarting with the R key
- Movement is controlled via arrow keys (UP, DOWN, LEFT, RIGHT)

We will discuss the implementation details with code examples to show how these objectives are achieved.

## 2. Classes and Tools

### 2.1 Inherit Methods

The [Snake](/include/game/snake/snake.hpp) class inherits pure virtual methods from the [IGame](/lib/libarcade/Arcade/game.hpp) interface. These methods establish a standard lifecycle for all games in the framework:

```cpp
void init() override;
void destroy() override;
void handleEvent(Events::Event evt, IDisplay& display) override;
void update(std::chrono::nanoseconds dt, Player& player) override;
void render(IDisplay& display) override;
void restart();

std::string_view gameTitle() const noexcept override { return "Snake - BAM"; }
```

### 2.2 Grid System

Similar to PacMan, Snake uses a grid-based movement system with a [Grid](/include/tools/grid.hpp) template:

```cpp
template<typename T>
struct Grid {
    int width;
    int height;
    std::vector<T> cells;
    
    // Constructor and methods...
    T getPosition(Vec2 pos) const;
    void setPosition(Vec2 pos, T value);
    Vec2 wrap(Vec2 pos) const;  // Handles edge wrapping
};
```

The Snake game grid is **60 cells wide by 30 cells tall**, providing a larger playing area than PacMan.

### 2.3 Snake Data Structure

The snake is represented as a **deque of Vec2 positions**, where the front element is the head and the back element is the tail:

```cpp
std::deque<Tools::Vec2> _snake;  // front = head
```

This deque structure allows efficient addition of new head segments and removal of tail segments.

### 2.4 Cell Types

The game uses the following cell types:
```cpp
enum CellType {
    WALL,      // Not used in Snake
    EMPTY,     // Empty cell
    APPLE,     // Food for the snake
    BODY,      // Snake body segment
    HEAD,      // Snake head
    PACGUN,    // Not used in Snake
    GHOST,     // Not used in Snake
    GATE,      // Not used in Snake
    GUMS       // Not used in Snake
};
```

## 3. Game Initialization and Setup

### 3.1 Constructor

The Snake constructor initializes the game state:

```cpp
Snake::Snake()
    : _rng( std::random_device{}() )
    , _grid(MAP_WIDTH, MAP_HEIGHT, Tools::EMPTY)
    , _nbApples(0)
    , _gameScore(0)
    , _accumulator(0)
    , _gameOver(false)
{
}
```

Key constants:
- **MAP_WIDTH**: 60 cells
- **MAP_HEIGHT**: 30 cells
- **TARGET_APPLES**: 3 (maximum apples on map)
- **APPLE_ATTEMPTS_MAX**: 100 (retry limit when spawning)
- **MOVE_DELAY**: 100 milliseconds (frame-rate independent movement)

### 3.2 Initialization (init)

The `init()` function sets up the game for a new playthrough:

```cpp
void Snake::init()
{
    _gameOver = false;
    _nbApples = 0;
    _accumulator = 0ns;
    _grid.reset(Tools::EMPTY);
    
    // Create initial snake (3 segments)
    for (int i = 0; i < 3; i++) {
        Tools::Vec2 coords = {MAP_WIDTH / 2 - i, MAP_HEIGHT / 2};
        _snake.push_back(coords);
        _grid.setPosition(coords, Tools::BODY);
    }
    
    // Mark head
    _grid.setPosition({MAP_WIDTH / 2, MAP_HEIGHT / 2}, Tools::HEAD);
    
    // Set initial direction
    _dir = Tools::Direction::RIGHT;
    _nextDir = _dir;
}
```

The snake starts at the **center of the map** with **3 body segments** arranged horizontally.

### 3.3 Random Coordinate Generation

The `getRandomEmptyCoord()` function finds an unoccupied cell for spawning apples:

```cpp
std::optional<Tools::Vec2> Snake::getRandomEmptyCoord()
{
    std::uniform_int_distribution<Arcade::Coordinate> distX(0, MAP_WIDTH);
    std::uniform_int_distribution<Arcade::Coordinate> distY(0, MAP_HEIGHT);
    
    Tools::Vec2 coords = {distX(_rng), distY(_rng)};
    
    for (size_t i = 0; i < APPLE_ATTEMPTS_MAX; ++i) {
        if (_grid.getPosition(coords) == Tools::EMPTY)
            return coords;
        coords = {distX(_rng), distY(_rng)};
    }
    return {};  // Failed to find empty space
}
```

This function attempts up to 100 times to find an empty cell. If unsuccessful, it returns `std::nullopt`.

### 3.4 Apple Spawning

The `spawnApple()` function adds new apples to the map:

```cpp
bool Snake::spawnApple()
{
    if (_nbApples >= TARGET_APPLES)
        return false;
    
    auto appleCoords = getRandomEmptyCoord();
    if (!appleCoords)
        return false;
    
    _grid.setPosition(*appleCoords, Tools::APPLE);
    _nbApples++;
    return true;
}
```

Apples are only spawned if:
- The current apple count is below the maximum (3)
- A valid empty cell is found

## 4. Game Update Logic

### 4.1 Movement System

Like PacMan, Snake uses a time-accumulator pattern for frame-rate independent movement:

```cpp
_accumulator += dt;
if (_accumulator < MOVE_DELAY)
    return;
_accumulator -= MOVE_DELAY;
```

The snake moves one cell every 100 milliseconds.

### 4.2 Snake Movement

Each update cycle, the snake moves in the queued direction:

```cpp
_dir = _nextDir;  // Apply queued direction
auto nextCell = _grid.wrap(_snake.front() + _dir);

if (_grid.getPosition(nextCell) == Tools::APPLE) {
    // Eating logic (snake grows)
    eatApple();
    _gameScore += 1;
} else if (_grid.getPosition(nextCell) == Tools::BODY) {
    // Collision with self
    _gameOver = true;
} else {
    // Normal movement (body follows head)
    _grid.setPosition(_snake.back(), Tools::EMPTY);
    _snake.pop_back();
}
```

### 4.3 Movement Validation

The snake **cannot move backwards** into itself. This is prevented at the input handling level:

```cpp
case ARC_ARROW_UP: 
    return _nextDir = _dir != Dir::DOWN ? Dir::UP : _dir;
case ARC_ARROW_DOWN: 
    return _nextDir = _dir != Dir::UP ? Dir::DOWN : _dir;
case ARC_ARROW_LEFT: 
    return _nextDir = _dir != Dir::RIGHT ? Dir::LEFT : _dir;
case ARC_ARROW_RIGHT: 
    return _nextDir = _dir != Dir::LEFT ? Dir::RIGHT : _dir;
```

This prevents the snake from reversing and immediately colliding with itself.

### 4.4 Growth Mechanic

When the snake eats an apple:

```cpp
void Snake::eatApple()
{
    _nbApples--;
    spawnApple();
}
```

- The apple is removed from the map
- The snake **grows** (no tail segment is removed in the next movement)
- A new apple is immediately spawned to maintain the target count
- Score increases by 1

### 4.5 Collision Detection

Two collision types are checked:

1. **Apple Collision**: Snake head moves to apple position → growth
2. **Self Collision**: Snake head moves to a BODY cell → game over

The game ends when the snake collides with any part of its own body.

### 4.6 Grid Updates

After movement decisions are made, the grid is updated:

```cpp
_grid.setPosition(_snake.front(), Tools::BODY);  // Old head becomes body
_snake.push_front(nextCell);                      // New head added
_grid.setPosition(_snake.front(), Tools::HEAD);   // Mark new head
```

## 5. Game Rendering

### 5.1 Cell Color Mapping

The `getCellColor()` function determines how each cell type is displayed:

```cpp
Arcade::Color Snake::getCellColor(Tools::CellType type)
{
    switch (type)
    {
        case Tools::APPLE: 
            return Arcade::Colors::RED;
        case Tools::BODY: 
            return Arcade::Colors::CYAN;
        case Tools::HEAD: 
            return Arcade::Colors::GREEN;
        default: 
            return Arcade::Colors::BLACK;
    }
}
```

- **Apple**: Bright RED
- **Snake Body**: Cyan (light blue)
- **Snake Head**: Bright GREEN
- **Empty**: Black

### 5.2 Render Process

The render function draws the game in layers:

```cpp
void Snake::render(IDisplay& display)
{
    // Draw all grid cells with appropriate colors
    for (long x = 0; x < MAP_WIDTH; ++x) {
        for (long y = 0; y < MAP_HEIGHT; ++y) {
            display.draw(Arcade::Shapes::Point(x + 1, y + 1, 
                getCellColor(_grid.getPosition({x, y}))));
        }
    }
    
    // Draw game over message if needed
    if (_gameOver) {
        Arcade::Text endDialog("GAME OVER ! PRESS \'R\' to restart the game!");
        endDialog.x = (MAP_WIDTH - endDialog.content.size()) / 2;
        endDialog.y = MAP_HEIGHT / 2;
        display.draw(endDialog);
    }
    
    // Draw borders
    display.draw(Arcade::Shapes::Rectangle(0, 0, MAP_WIDTH + 2, 0, Arcade::Colors::WHITE));
    display.draw(Arcade::Shapes::Rectangle(0, 0, 0, MAP_HEIGHT + 2, Arcade::Colors::WHITE));
    display.draw(Arcade::Shapes::Rectangle(0, MAP_HEIGHT + 1, MAP_WIDTH + 2, 0, Arcade::Colors::WHITE));
    display.draw(Arcade::Shapes::Rectangle(MAP_WIDTH + 1, 0, 0, MAP_HEIGHT + 2, Arcade::Colors::WHITE));
    
    // Draw score
    Arcade::Text playerScoreText("Score: ");
    playerScoreText.content += std::to_string(_gameScore);
    playerScoreText.x = MAP_WIDTH + playerScoreText.content.length();
    playerScoreText.y = MAP_HEIGHT;
    display.draw(playerScoreText);
}
```

### 5.3 Render Layers

The rendering order is:
1. **Grid**: All cells with their respective colors
2. **Game Over Message**: Centered text (if applicable)
3. **Borders**: White rectangle frame around play area
4. **HUD**: Score display

## 6. Game State Management

### 6.1 State Variables

The Snake class maintains the following state:

```cpp
size_t _gameScore;                    // Current score
size_t _nbApples;                     // Number of apples on map
Tools::Grid<Tools::CellType> _grid;   // Game world
std::mt19937 _rng;                    // Random number generator
std::deque<Tools::Vec2> _snake;       // Snake segments (front = head)
Tools::Vec2 _dir;                     // Current direction
Tools::Vec2 _nextDir;                 // Queued direction
std::chrono::nanoseconds _accumulator;// Time accumulator
bool _gameOver;                       // Game state flag
```

### 6.2 Input Handling

The `handleEvent()` function processes keyboard input:

```cpp
void Snake::handleEvent(Events::Event evt, IDisplay&)
{
    namespace Dir = Tools::Direction;
    switch (evt)
    {
    case ARC_ARROW_UP: 
        return _nextDir = _dir != Dir::DOWN ? Dir::UP : _dir;
    case ARC_ARROW_DOWN: 
        return _nextDir = _dir != Dir::UP ? Dir::DOWN : _dir;
    case ARC_ARROW_LEFT: 
        return _nextDir = _dir != Dir::RIGHT ? Dir::LEFT : _dir;
    case ARC_ARROW_RIGHT: 
        return _nextDir = _dir != Dir::LEFT ? Dir::RIGHT : _dir;
    case ARC_KEY_R: 
        return restart();
    default:
        return;
    }
}
```

### 6.3 Cleanup and Restart

The `destroy()` function frees resources:

```cpp
void Snake::destroy()
{
    _grid.cells.clear();
    _grid.cells.shrink_to_fit();
    _snake.clear();
    _snake.shrink_to_fit();
}
```

The `restart()` function resets the game:

```cpp
void Snake::restart()
{
    _gameScore = 0;
    destroy();
    init();
}
```

## 7. Game Loop Summary

Each frame update follows this sequence:

1. **Check Game State**: If game over, skip remaining updates
2. **Update Score**: Sync player score with current game score
3. **Accumulate Time**: Add delta time to accumulator
4. **Check Movement Delay**: Only proceed if enough time has passed
5. **Update Direction**: Apply queued direction input
6. **Calculate Next Cell**: Apply current direction and wrap edges
7. **Check Collision**:
   - Apple: Call `eatApple()`, increment score
   - Body: Set `_gameOver = true`
8. **Update Grid**: Remove tail, add head, update cell types
9. **Spawn Apple**: Maintain target apple count
10. **Render**: Draw all game elements to display

## 8. Key Differences from PacMan

- **No static obstacles**: No walls or gates to navigate around
- **Growth mechanics**: Snake grows when eating, doesn't shrink naturally
- **Self collision**: Primary threat is the snake's own body
- **Simpler map**: Larger grid with no complex zones
- **Larger play area**: 60x30 cells vs. PacMan's 30x15
- **No power-ups**: No special items that change game behavior
- **No NPCs**: No ghosts with independent AI

## 9. Conclusion

The Snake implementation demonstrates:
- **Simple but engaging game mechanics** using grid-based movement
- **Time-accumulator pattern** for smooth, frame-rate independent gameplay
- **Deque data structure** for efficient snake segment management
- **Input validation** to prevent invalid moves
- **Random element placement** using retry logic
- **Clear separation of concerns** with dedicated functions for each mechanic

This design provides a solid foundation for extending Snake with features such as difficulty levels, obstacle walls, or power-up items.
