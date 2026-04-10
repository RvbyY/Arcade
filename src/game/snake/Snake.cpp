/*
** EPITECH PROJECT, 2026
** Arcade - Snake game library (skeleton)
*/

#include "game/snake/snake.hpp"
#include "../lib/libarcade/Arcade/display.hpp"
#include "../lib/libarcade/Arcade/utils.hpp"

namespace Arcade {

using std::chrono_literals::operator ""ns;

Snake::Snake()
    : _rng( std::random_device{}() )
    , _grid(MAP_WIDTH, MAP_HEIGHT, Tools::EMPTY)
    , _nbApples(0)
    , _gameScore(0)
    , _accumulator(0)
    , _gameOver(false)
{

}

std::optional<Tools::Vec2> Snake::getRandomEmptyCoord()
{
    std::uniform_int_distribution<Arcade::Coordinate> distX(0, MAP_WIDTH);
    std::uniform_int_distribution<Arcade::Coordinate> distY(0, MAP_HEIGHT);

    Tools::Vec2 coords = {distX(_rng), distY(_rng)};

    for (size_t i = 0 ;i < APPLE_ATTEMPTS_MAX; ++i) {
        if (_grid.getPosition(coords) == Tools::EMPTY)
            return coords;
        coords = {distX(_rng), distY(_rng)};
    }
    return {};
}

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

void Snake::eatApple()
{
    _nbApples--;
    spawnApple();
}

void Snake::init()
{
    _gameOver = false;
    _nbApples = 0;
    _accumulator = 0ns;
    _grid.reset(Tools::EMPTY);
    for (int i = 0; i < 3; i++) {
        Tools::Vec2 coords = {MAP_WIDTH / 2 - i, MAP_HEIGHT / 2};
        _snake.push_back(coords);
        _grid.setPosition(coords, Tools::BODY);
    }
    _grid.setPosition({MAP_WIDTH / 2, MAP_HEIGHT / 2}, Tools::HEAD);
    _dir = Tools::Direction::RIGHT;
    _nextDir = _dir;
}

void Snake::destroy()
{
    _grid.cells.clear();
    _grid.cells.shrink_to_fit();
    _snake.clear();
    _snake.shrink_to_fit();
}

void Snake::restart()
{
    _gameScore = 0;
    destroy();
    init();
}

void Snake::handleEvent(Events::Event evt, IDisplay&)
{
    namespace Dir = Tools::Direction;
    switch (evt)
    {
    case ARC_ARROW_UP: return _nextDir = _dir != Dir::DOWN ? Dir::UP : _dir;
    case ARC_ARROW_DOWN: return _nextDir = _dir != Dir::UP ? Dir::DOWN : _dir;
    case ARC_ARROW_LEFT: return _nextDir = _dir != Dir::RIGHT ? Dir::LEFT : _dir;
    case ARC_ARROW_RIGHT: return _nextDir = _dir != Dir::LEFT ? Dir::RIGHT : _dir;
    case ARC_KEY_R : return restart();
    default:
        return;
    }
}

void Snake::update(std::chrono::nanoseconds dt, Player& player)
{
    if (_gameOver)
        return;
    player.score = _gameScore;
    _accumulator+=dt;
    if (_accumulator < MOVE_DELAY)
        return;
    _accumulator -= MOVE_DELAY;

    _dir = _nextDir;
    auto nextCell = _grid.wrap(_snake.front() + _dir);
    if (_grid.getPosition(nextCell) == Tools::APPLE) {
        eatApple();
        _gameScore += 1;
    } else if (_grid.getPosition(nextCell) == Tools::BODY)
    {
        _gameOver = true;
    } else {
        _grid.setPosition(_snake.back(), Tools::EMPTY);
        _snake.pop_back();
    }

    _grid.setPosition(_snake.front(), Tools::BODY);
    _snake.push_front(nextCell);
    _grid.setPosition(_snake.front(), Tools::HEAD);
    spawnApple();
}

Arcade::Color Snake::getCellColor(Tools::CellType type)
{
    switch (type)
    {
        case Tools::APPLE: return Arcade::Colors::RED;
        case Tools::BODY: return Arcade::Colors::CYAN;
        case Tools::HEAD: return Arcade::Colors::GREEN;
        default: return Arcade::Colors::BLACK;
    }
}

void Snake::render(IDisplay& display)
{
    for (long x = 0; x < MAP_WIDTH; ++x) {
        for (long y = 0; y < MAP_HEIGHT; ++y) {
            display.draw(Arcade::Shapes::Point(x + 1, y + 1, getCellColor(_grid.getPosition({x, y}))));
        }
    }
    if (_gameOver) {
        Arcade::Text endDialog("GAME OVER ! PRESS \'R\' to restart the game!");

        endDialog.x = (MAP_WIDTH - endDialog.content.size()) / 2;
        endDialog.y = MAP_HEIGHT / 2;

        display.draw(endDialog);
    }

    display.draw(Arcade::Shapes::Rectangle(0, 0, MAP_WIDTH + 2, 0, Arcade::Colors::WHITE));
    display.draw(Arcade::Shapes::Rectangle(0, 0, 0, MAP_HEIGHT + 2, Arcade::Colors::WHITE));
    display.draw(Arcade::Shapes::Rectangle(0, MAP_HEIGHT + 1, MAP_WIDTH + 2, 0, Arcade::Colors::WHITE));
    display.draw(Arcade::Shapes::Rectangle(MAP_WIDTH + 1, 0, 0, MAP_HEIGHT + 2, Arcade::Colors::WHITE));

}

} // namespace Arcade

extern "C" Arcade::IGame* get_game()
{
    return new Arcade::Snake();
}
