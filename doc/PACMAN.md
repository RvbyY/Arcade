# PACMAN Documentation


## 1. Introduction

This document describes the PacMan game architecture and thinking applied to make it works.

The goals of the game are:

- The game area has a specific size. Going through one side of the area makes the player appear on
  the opposite side. All cells that are not walls may be walked through and contain ”pacgums”.
* In the middle of the map is a small 5-cell-wide and 4-cell-high area that contains ghosts.
* Ghosts can get out of their box 10 seconds after the game starts.
* Pacman starts the game right under the ghosts.
* Some special, larger ”pacgums” let Pacman eat ghosts. This effect lasts 10 seconds. During this pe-
riod, ghosts become blue and flee Pacman instead of hunting him. Their movement speed is slower
during this time. There are only 4 ”pacgums” of this kind on the map.
* When Pacman eats a ghost, only its eyes remain. These eyes quickly go back to the ghost box, where
the ghost is healed after a short period of time.
* The player wins when Pacman eats all the ”pacgums”. A new map is loaded after that, or the current
one is reloaded and movement is accelerated.

We will discuss about these objectives with some code to show how does we manage thus succeed.


## 2. Classes and tools

### 2.1 Inherit methods

The `PacMan` class from [pacman.hpp](/include/game/pacman/pacman.hpp) inherit pure methods from `IGame` ([game.hpp](/lib/libarcade/Arcade/game.hpp)) Interface. These are setups helper to launch, render, restart and close the game. Inherence tell to every game how should it works to follow and same architecture and limit conflict between them. It's looks like this:
```cpp
            void init() override;
            void destroy() override;
            void handleEvent(Events::Event evt, IDisplay& display) override;
            void update(std::chrono::nanoseconds dt, Player& player) override;
            void render(IDisplay& display) override;
            void setPacmanPosition();
            void setGhostsPositions();
            void restart();

            std::string_view gameTitle() const noexcept override { return "PacMan - BAM"; }
```

### 2.2 Grid and Cells

To move our player, ghosts and spwan some pacgums, we though making a grid with cells, to make them move with maths formula (increment/decrement x or y) is the way to do it. So we created a `Grid` struct to build our map with operations (get and set item positions) into [grid.hpp](/include/tools/grid.hpp):
```cpp
    template<typename T>
    struct Grid {
            int width;
            int height;
            std::vector<T> cells;

            Grid(int w, int h, T defaultValue = T{}) : width(w), height(h), cells(w * h, defaultValue) {}
            ~Grid() = default;

            // Constructor and methods...
            void reset(T value)
            {
                cells = std::vector<T>(width * height, value);
            }

            int index(Vec2 pos) const
            {
                return pos.y * width + pos.x;
            }

            bool inBounds(Vec2 pos) const
            {
                return pos.x >= 0 && pos.x < width
                    && pos.y >= 0 && pos.y < height;
            }

            T getPosition(Vec2 pos) const
            {
                return cells[index(pos)];
            }

            void setPosition(Vec2 pos, T value)
            {
                cells[index(pos)] = value;
            }

            // Handles edge wrapping
            Vec2 wrap(Vec2 pos) const
            {
                return {
                    ((pos.x % width) + width) % width,
                    ((pos.y % height) + height) % height
                };
            }
    };
```

The template **T** is here to fill our grid with the type of value we want to (int, celltype...).

`Vec2` Type to keep our elements into 2D (x and y value) and an enum type:
```cpp
    struct Vec2 {
        Arcade::Coordinate x;
        Arcade::Coordinate y;

        // Operators to make easier interactions between Vec2 elements
        Vec2 operator+(const Vec2& other) const
        {
            return {
                x + other.x, y + other.y
            };
        }

        Vec2 operator-(const Vec2& other) const
        {
            return {
                x - other.x, y - other.y
            };
        }

        void operator=(const Vec2& other)
        {
            x = other.x;
            y = other.y;
        }

        bool operator==(const Vec2& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vec2& other) const
        {
            return !(*this == other);
        }
    };
```
`Celltype` to manage cells of our grid in our games:
```cpp
enum CellType {
        WALL,       // Wall cell
        EMPTY,      // Empty cell
        APPLE,      // Not used in Pacman
        BODY,       // Not used in Pacman
        HEAD,       // Pacman cell
        PACGUN,     // Super PacGums cell
        GHOST,      // Ghost cell
        GATE,       // Gate cell
        GUMS,       // PacGums cell
    };
```

All of them are in a **Tools** namespace.

## 3. Game Initialization and Setup

### 3.1 Constructor and Initialization

The PacMan constructor initializes all game state variables and creates a 4-ghost deque:
```cpp
PacMan::PacMan()
    : _rng( std::random_device{}() )
    , _grid(MAP_WIDTH, MAP_HEIGHT, Tools::EMPTY)
    , _nbPacGun(0)
    , _accumulator(0)
    , _gameScore(0)
    , _gameOver(false)
    , _gameWon(false)
    , _superPac(false)
    , _superPacTimer(0)
    , _ghostFrozenUntil{0ns, 0ns, 0ns, 0ns}
    , _ghostPoint{0, 0, 0, 0}
{
    _ghosts.resize(4, {0, 0});
}
```

The map dimensions are constant at **30x15 cells**, with a ghost zone of **5x4 cells** centered in the middle.

### 3.2 Map Creation

The `createMap()` function generates a randomized map with walls and creates the ghost zone in the center:
- Randomly places walls across the map (approximately 20% of cells)
- Creates a **5x4 ghost containment zone** in the center with walls on all sides
- Places a **gate** (opening) at the bottom of the ghost zone so ghosts can exit
- Fills all non-wall cells with gums (food pellets)

### 3.3 Positioning Functions

**setPacmanPosition()**: Places Pacman at a random gum location on the map, or defaults to the center if no valid position is found. Initial direction is set to RIGHT.

**setGhostsPositions()**: Initializes all 4 ghosts inside the ghost zone:
```cpp
for (int i = 0; i < 4; i++) {
    _ghosts[i] = {offsetX + 2 + (i % 2), offsetY + 2 + (i / 2)};
}
```

### 3.4 Special Pacgum Spawning

The `spawnPacGun()` function spawns special power-up pacgums (maximum of 4 on the map):
- Targets a random empty gum location
- Marks it as a PACGUN cell type
- These are visually distinct and give Pacman temporary invulnerability

## 4. Game Update Logic

### 4.1 Movement System

The game uses a time-accumulator system to control movement speed:
```cpp
_accumulator += dt;
if (_accumulator < MOVE_DELAY)
    return;
_accumulator -= MOVE_DELAY;
```

**MOVE_DELAY** defaults to 100ms, making Pacman and ghosts move one cell every 100 milliseconds.

### 4.2 Pacman Movement

Pacman moves in the direction set by the last key press:
1. Calculate next cell position using the current direction
2. Check if the next cell is walkable (not a wall or gate)
3. If walkable, move Pacman to the next cell
4. Handle wrapping at map edges using the grid's `wrap()` function

### 4.3 Gum Eating Mechanic

When Pacman moves to a cell with gums:
- The gum is removed from that cell
- Player score increases by 1 point
- The cell becomes EMPTY

### 4.4 Special Pacgum Effects

When Pacman eats a pacgum (PACGUN):
1. **Super Mode Activated**: `_superPac = true`
2. **Movement Speed Increases**: MOVE_DELAY changes to 200ms (slower, more deliberate)
3. **Score Bonus**: +10 points for each pacgum eaten
4. **Duration Timer**: `_superPacTimer` resets to track the 10-second duration
5. **Visual Feedback**: Pacman and ghosts change color when super mode is active

### 4.5 Ghost Behavior

Ghosts move independently using a random pathfinding algorithm:
```cpp
void PacMan::moveGhosts(int ghostIndex)
{
    // Find all valid adjacent moves
    std::vector<Tools::Vec2> validMoves;
    Tools::Vec2 directions[] = {
        {ghostPos.x + 1, ghostPos.y},  // Right
        {ghostPos.x - 1, ghostPos.y},  // Left
        {ghostPos.x, ghostPos.y + 1},  // Down
        {ghostPos.x, ghostPos.y - 1}   // Up
    };
    
    // Filter out walls and gates
    for (const auto& dir : directions) {
        if (_grid.getPosition(_grid.wrap(dir)) != Tools::WALL) {
            validMoves.push_back(wrapped);
        }
    }
    
    // Pick a random valid move
    if (!validMoves.empty()) {
        _ghosts[ghostIndex] = validMoves[random_selection];
    }
}
```

**Super Mode Ghost Behavior**: When Pacman is in super mode, ghosts become frozen for 10 seconds and cannot move.

### 4.6 Collision Detection

Collision with ghosts is checked after all movements:
- **Normal Mode**: Collision = Game Over
- **Super Mode**: Ghost is defeated (sent back to spawn zone, frozen for 10 seconds, +20 points)

### 4.7 Win Condition

The player wins when all regular gums are eaten (`_nbPacGun == 0`). At this point:
- `_gameWon = true`
- Game displays "YOU WON" message
- Player can press R to restart

## 5. Game Rendering

### 5.1 Cell Color Mapping

The `getCellColor()` function determines how each cell type is displayed:
```cpp
Arcade::Color PacMan::getCellColor(Tools::CellType type)
{
    switch (type)
    {
        case Tools::GHOST: 
            return _superPac ? Colors::GREEN : Colors::RED;
        case Tools::HEAD: 
            return _superPac ? Colors::PURPLE : Colors::YELLOW;
        case Tools::WALL: 
            return Colors::BLUE;
        case Tools::GATE: 
            return Colors::PURPLE;
        case Tools::PACGUN: 
            return ORANGE;
        case Tools::EMPTY: 
            return Colors::BLACK;
        case Tools::GUMS: 
            return Colors::WHITE;
        default: 
            return Colors::BLACK;
    }
}
```

### 5.2 Render Layers

The render function draws in order:
1. **Background**: Black fill for the entire game area
2. **Grid**: All cells with their respective colors
3. **Special Elements**: Pacguns, ghosts, and Pacman drawn on top
4. **Ghost Zone Border**: Cyan rectangle outline showing the containment zone
5. **Game Border**: Blue rectangle around the entire play area
6. **HUD**: Score display in the top-right corner
7. **End Screen**: "GAME OVER" or "YOU WON" dialog with restart instructions

### 5.3 End Game Dialog

When the game ends, a centered dialog box appears with:
- Title ("GAME OVER" in RED or "YOU WON" in GREEN)
- Instructions to press R to restart
- Semi-transparent black background with colored borders

## 6. Game State Management

### 6.1 Game States

The PacMan class maintains several boolean flags:
- **`_gameOver`**: Set when Pacman collides with a ghost in normal mode
- **`_gameWon`**: Set when all gums are eaten
- **`_superPac`**: Tracks whether Pacman is in invulnerability mode
- **`_superPacTimer`**: Countdown timer for super mode duration (10 seconds)
- **`_ghostFrozenUntil`**: Array tracking freeze duration for each ghost individually

### 6.2 Restart Mechanism

The `restart()` function:
1. Resets game score to 0
2. Calls `destroy()` to clean up the grid and entities
3. Calls `init()` to reinitialize the game state

### 6.3 Input Handling

The `handleEvent()` function maps keyboard input to Pacman direction:
- **Arrow Up**: Direction UP
- **Arrow Down**: Direction DOWN
- **Arrow Left**: Direction LEFT
- **Arrow Right**: Direction RIGHT
- **R Key**: Restart the game

## 7. Game Loop Summary

Each frame update follows this sequence:

1. **Accumulate Time**: Add delta time to accumulator
2. **Check Movement Delay**: Only proceed if accumulator exceeds MOVE_DELAY
3. **Move Pacman**: Calculate next position and move if valid
4. **Eat Regular Gums**: If cell contains gums, increase score and clear cell
5. **Check Pacgums**: If cell contains special pacgum, activate super mode
6. **Move Ghosts**: Move each ghost that isn't frozen
7. **Collision Detection**: Check Pacman vs. all ghosts
8. **Update Super Mode**: Decrement timer, deactivate if duration expires
9. **Check Win Condition**: Set win flag if no gums remain
10. **Render**: Draw all game elements to display

## 8. Conclusion

The PacMan implementation demonstrates a classic game architecture using:
- **Grid-based movement** for simplicity and precision
- **Time-accumulator pattern** for frame-rate independent movement
- **State machines** for tracking game conditions
- **Random pathfinding** for ghost behavior
- **Color-coded rendering** for clear visual feedback

This modular design makes it easy to extend with additional features such as different ghost AI strategies, difficulty levels, or advanced power-ups.