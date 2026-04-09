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
    std::uniform_int_distribution<Arcade::Coordinate> distX(0, MAP_WIDTH - 1);  // Now 0 to 59
    std::uniform_int_distribution<Arcade::Coordinate> distY(0, MAP_HEIGHT - 1);  // 0 to 29
    Tools::Vec2 coords = {distX(_rng), distY(_rng)};

    for (size_t i = 0; i < GUN_MAX_ATTEMPs; i++) {
        if (_grid.getPosition(coords) == Tools::EMPTY)
            return coords;
        coords = {distX(_rng), distY(_rng)};
    }
    return {};
}

void PacMan::setPacmanPosition()
{
    int z = 0;

    Tools::Vec2 coords = {MAP_WIDTH / 2, MAP_HEIGHT / 2};
    while (_grid.getPosition(coords) == Tools::WALL) {
        if (coords.x < MAP_WIDTH / 2)
            coords.x++;
        else
            coords.x--;
        if (z % 5 == 0)
            coords.y++;
        z++;
    }
    _pacman = coords;
    _grid.setPosition(coords, Tools::HEAD);
    _dir = Tools::Direction::RIGHT;
}

void PacMan::setGhostsPositions()
{
    Tools::Vec2 coords;

    for (int i = 0; i < 4; i++) {
        if (i == 0 || i % 2 == 0)
            coords = {GHOST_ZONE_WIDTH - 1 - i, GHOST_ZONE_HEIGHT - 1};
        else
            coords = {GHOST_ZONE_WIDTH - 1, GHOST_ZONE_HEIGHT - 1 - i};
        _ghosts.push_back(coords);
        _grid.setPosition(coords, Tools::GHOST);
    }
}

bool PacMan::spawnPacGun()
{
    if (_nbPacGun >= TARGET_GUN)
        return false;
    auto pacGunCoords = getRandomEmptyCoord();

    if (!pacGunCoords)
        return false;
    _grid.setPosition(*pacGunCoords, Tools::PACGUN);
    _nbPacGun++;
    return true;
}

void PacMan::eatPacGun()
{
    _nbPacGun--;
    PacMan::spawnPacGun();
}

void PacMan::init()
{
    std::uniform_int_distribution<int> dist(0, 100);

    for (unsigned int i = 0; i < 1800; i++) {
        int randomValue = dist(_rng);
        if (randomValue < 40)
            _grid.cells[i] = Tools::WALL;
        else
            _grid.cells[i] = Tools::EMPTY;
    }
    PacMan::setPacmanPosition();
    PacMan::setGhostsPositions();
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (_grid.getPosition({x, y}) == Tools::EMPTY) {
                _grid.setPosition({x, y}, Tools::PACGUN);
                _nbPacGun++;
            }
        }
    }
}

}