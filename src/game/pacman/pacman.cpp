/*
** EPITECH PROJECT, 2026
** Arcade - PacMan game library (sheleton)
*/

#include "game/pacman/pacman.hpp"
#include "display.hpp"
#include "utils.hpp"

namespace Arcade {

using std::chrono_literals::operator ""ns;

PacMan::PacMan()
    : _rng( std::random_device{}() )
    , _grid(MAP_WIDTH, MAP_HEIGHT, Tools::EMPTY)
    , _nbPacGun(0)
    , _accumulator(0)
    , _gameOver(false)
{}

std::optional<Tools::Vec2> PacMan::getRandomEmptyCoord()
{
    std::uniform_int_distribution<Arcade::Coordinate> distX(0, MAP_WIDTH);
    std::uniform_int_distribution<Arcade::Coordinate> distY(0, MAP_HEIGHT);
}

}