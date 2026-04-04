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
    , nbApples(0)
    , _accumulator(0)
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
    auto appleCoords = getRandomEmptyCoord();

    if (!appleCoords || nbApples >= TARGET_APPLES)
        return false;
    _grid.setPosition(*appleCoords, Tools::APPLE);
    nbApples++;
    return true;
}

void Snake::init()
{
    nbApples = 0;
    _accumulator = 0ns;
    _grid.reset(Tools::EMPTY);
}

void Snake::destroy()
{
    // TODO
}

void Snake::handleEvent(Events::Event evt, IDisplay&)
{
   // TODO
}

void Snake::update(std::chrono::nanoseconds dt, Player& player)
{
    _accumulator+=dt;
}

Arcade::Color Snake::getCellColor(Tools::CellType type)
{
    switch (type)
    {
        case Tools::APPLE: return Arcade::Colors::RED;
        case Tools::BODY: return Arcade::Colors::GREEN;
        case Tools::HEAD: return 0x00aa00;
        default: return Arcade::Colors::BLACK;
    }
}

void Snake::render(IDisplay& display)
{
    for (int i = 0; i < 3; i++)
        spawnApple();
    for (long x = 0; x < MAP_WIDTH; ++x) {
        for (long y = 0; y < MAP_HEIGHT; ++y) {

            display.draw(Arcade::Shapes::Point(x, y, getCellColor(_grid.getPosition({x, y}))));
        }
    }
}

} // namespace Arcade

extern "C" Arcade::IGame* get_game()
{
    return new Arcade::Snake();
}
