/*
** EPITECH PROJECT, 2026
** Arcade - PacMan game library (sheleton)
*/

#include "game/pacman/pacman.hpp"
#include "../lib/libarcade/Arcade/display.hpp"
#include "../lib/libarcade/Arcade/utils.hpp"
#include <chrono>

namespace Arcade {

using std::chrono_literals::operator ""ns;
using std::chrono_literals::operator ""s;

PacMan::PacMan()
    : _rng( std::random_device{}() )
    , _grid(MAP_WIDTH, MAP_HEIGHT, Tools::EMPTY)
    , _nbPacGun(0)
    , _accumulator(0)
    , _gameOver(false)
    , _gameWon(false)
    , _superPac(false)
    , _superPacTimer(0)
    , _ghostFrozenUntil{0ns, 0ns, 0ns, 0ns}
    , _ghostPoint{0, 0, 0, 0}
{
    _ghosts.resize(4, {0, 0});
}

std::optional<Tools::Vec2> PacMan::getRandomEmptyCoord()
{
    std::uniform_int_distribution<Arcade::Coordinate> distX(0, MAP_WIDTH - 1);
    std::uniform_int_distribution<Arcade::Coordinate> distY(0, MAP_HEIGHT - 1);
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

    Tools::Vec2 coords = {0, 0};
    while (_grid.getPosition(coords) == Tools::WALL) {
        if (coords.x < MAP_WIDTH / 2)
            coords.x++;
        else if (z % 5 == 0)
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
    int offsetX = GHOST_ZONE_CENTER_X - GHOST_ZONE_WIDTH / 2;
    int offsetY = GHOST_ZONE_CENTER_Y - GHOST_ZONE_HEIGHT / 2;

    for (int i = 0; i < 4; i++) {
        if (i == 0 || i % 2 == 0)
            coords = {offsetX + GHOST_ZONE_WIDTH - 1 - i, offsetY + GHOST_ZONE_HEIGHT - 1};
        else
            coords = {offsetX + GHOST_ZONE_WIDTH - 1, offsetY + GHOST_ZONE_HEIGHT - 1 - i};
        _ghosts[i] = coords;
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

void PacMan::eatPacGun(Player& player)
{
    _nbPacGun--;
    _superPac = true;
    // PacMan::spawnPacGun();
    player.score += 10;
}

void PacMan::createMap(int randomValue, std::uniform_int_distribution<int> dist)
{
    int offsetX = GHOST_ZONE_CENTER_X - GHOST_ZONE_WIDTH / 2;
    int offsetY = GHOST_ZONE_CENTER_Y - GHOST_ZONE_HEIGHT / 2;
    int gateX = offsetX + GHOST_ZONE_WIDTH / 2;
    int gateY = offsetY + GHOST_ZONE_HEIGHT;

    for (unsigned int i = 0; i < 1800; i++) {
        randomValue = dist(_rng);
        if (randomValue < 20)
            _grid.cells[i] = Tools::WALL;
        else
            _grid.cells[i] = Tools::EMPTY;
    }
    for (int x = offsetX + 1; x < offsetX + GHOST_ZONE_WIDTH; x++) {
        _grid.setPosition({x, offsetY}, Tools::WALL);
    }
    for (int y = offsetY + 1; y < offsetY + GHOST_ZONE_HEIGHT; y++) {
        _grid.setPosition({offsetX, y}, Tools::WALL);
    }
    for (int y = offsetY + 1; y < offsetY + GHOST_ZONE_HEIGHT; y++) {
        _grid.setPosition({offsetX + GHOST_ZONE_WIDTH - 1, y}, Tools::WALL);
    }
    for (int x = offsetX + 1; x < offsetX + GHOST_ZONE_WIDTH; x++) {
        if (x == gateX || x == gateX + 1) {
            _grid.setPosition({x, gateY}, Tools::GATE);
        } else {
            _grid.setPosition({x, gateY}, Tools::WALL);
        }
    }
}

void PacMan::init()
{
    std::uniform_int_distribution<int> dist(0, 100);
    int randomValue;

    _grid.reset(Tools::EMPTY);
    _pacGuns.clear();
    _nbPacGun = 0;
    _gameOver = false;
    _superPac = false;
    _superPacTimer = 0ns;
    for (int i = 0; i < 4; i++)
        _ghostFrozenUntil[i] = 0ns;
    createMap(randomValue, dist);
    PacMan::setPacmanPosition();
    PacMan::setGhostsPositions();
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            randomValue = dist(_rng);
            Tools::Vec2 pos = {x, y};
            Tools::CellType cellType = _grid.getPosition(pos);
            if (_grid.getPosition(pos) == Tools::EMPTY && randomValue < 1) {
                if (spawnPacGun());
                    _pacGuns.insert(pos);
            }
        }
    }
}

void PacMan::destroy()
{
    _grid.reset(Tools::EMPTY);
    for (auto& ghost : _ghosts)
        ghost = {0, 0};
    _pacGuns.clear();
    _nbPacGun = 0;
}

void PacMan::restart()
{
    destroy();
    init();
}

void PacMan::handleEvent(Events::Event evt, IDisplay&)
{
    namespace Dir = Tools::Direction;
    switch (evt) {
        case ARC_ARROW_UP: return _dir = Dir::UP;
        case ARC_ARROW_DOWN: return _dir = Dir::DOWN;
        case ARC_ARROW_LEFT: return _dir = Dir::LEFT;
        case ARC_ARROW_RIGHT: return _dir = Dir::RIGHT;
        case ARC_KEY_R : return restart();
        default:
            return;
    }
}

void PacMan::eatGhosts(Player& player)
{
    if (_superPac) {
        int offsetX = GHOST_ZONE_CENTER_X - GHOST_ZONE_WIDTH / 2;
        int offsetY = GHOST_ZONE_CENTER_Y - GHOST_ZONE_HEIGHT / 2;
        for (int i = 0; i < 4; i++) {
            if (_pacman == _ghosts[i]) {
                _grid.setPosition(_ghosts[i], Tools::EMPTY);
                _ghosts[i] = {offsetX + 2 + (i % 2), offsetY + 2 + (i / 2)};
                _grid.setPosition(_ghosts[i], Tools::GHOST);
                _ghostFrozenUntil[i] = _accumulator + 2s;
            }
        }
        player.score += 20;
    }
}

void PacMan::superPacActions(Player& player)
{
    _superPacTimer = 0ns;
    eatGhosts(player);
}

void PacMan::moveGhosts(int ghostIndex)
{
    Tools::Vec2 ghostPos = _ghosts[ghostIndex];
    std::vector<Tools::Vec2> validMoves;
    Tools::Vec2 directions[] = {
        {ghostPos.x + 1, ghostPos.y},
        {ghostPos.x - 1, ghostPos.y},
        {ghostPos.x, ghostPos.y + 1},
        {ghostPos.x, ghostPos.y - 1}
    };

    for (const auto& dir : directions) {
        Tools::Vec2 wrapped = _grid.wrap(dir);
        if (_grid.getPosition(wrapped) != Tools::WALL) {
            validMoves.push_back(wrapped);
        }
    }
    if (!validMoves.empty()) {
        std::uniform_int_distribution<size_t> dist(0, validMoves.size() - 1);
        Tools::Vec2 newPos = validMoves[dist(_rng)];
        _grid.setPosition(_ghosts[ghostIndex], Tools::EMPTY);
        _ghosts[ghostIndex] = newPos;
        _grid.setPosition(newPos, Tools::GHOST);
    }
}

void PacMan::update(std::chrono::nanoseconds dt, Player& player)
{
    if (_gameOver || _gameWon)
        return;
    _superPacTimer += dt;
    _accumulator += dt;
    if (_accumulator < MOVE_DELAY)
        return;
    _accumulator -= MOVE_DELAY;
    auto nextCell = _grid.wrap(_pacman + _dir);

    for (int i = 0; i < 4; i++) {
        if (_pacman == _ghosts[i]) {
            if (_superPac) {
                eatGhosts(player);
            } else {
                _gameOver = true;
            }
        }
        if (_ghostFrozenUntil[i] < _accumulator)
            PacMan::moveGhosts(i);
    }

    if (_grid.getPosition(nextCell) != Tools::WALL && _grid.getPosition(nextCell) != Tools::GATE) {
        _grid.setPosition(_pacman, Tools::EMPTY);
        _pacman = nextCell;
        _grid.setPosition(_pacman, Tools::HEAD);
    }
    if (_pacGuns.count(nextCell) > 0) {
        _pacGuns.erase(nextCell);
        eatPacGun(player);
        superPacActions(player);
    }
    if (_superPac && _superPacTimer > 10s)
        _superPac = false;
    if (_nbPacGun == 0)
        _gameWon = true;
}

void PacMan::render(IDisplay& display)
{
    int offsetX = GHOST_ZONE_CENTER_X - GHOST_ZONE_WIDTH / 2;
    int offsetY = GHOST_ZONE_CENTER_Y - GHOST_ZONE_HEIGHT / 2;

    display.clear();
    for (long x = 0; x < MAP_WIDTH + 2; x++)
        for (long y = 0; y < MAP_HEIGHT + 2; y++)
            display.draw(Arcade::Shapes::Point(x, y, Arcade::Colors::BLACK));
    for (long x = 0; x < MAP_WIDTH; x++)
        for (long y = 0; y < MAP_HEIGHT; ++y)
            display.draw(Arcade::Shapes::Point(x + 1, y + 1, getCellColor(_grid.getPosition({x, y}))));
    for (const auto& pacGun : _pacGuns)
        display.draw(Arcade::Shapes::Point(pacGun.x + 1, pacGun.y + 1, Arcade::Colors::WHITE));
    if (_gameOver) {
        Arcade::Text endDialog("GAME OVER ! PRESS \'R\' to restart the game!");

        endDialog.x = (MAP_WIDTH - endDialog.content.size()) / 2;
        endDialog.y = MAP_HEIGHT / 2;
        display.draw(endDialog);
    }
    if (_gameWon) {
        Arcade::Text endDialog("CONGRATULATIONS ! YOU WON THE GAME ! PRESS \'R\' to restart the game!");

        endDialog.x = (MAP_WIDTH - endDialog.content.size()) / 2;
        endDialog.y = MAP_HEIGHT / 2;
        display.draw(endDialog);
    }
    display.draw(Arcade::Shapes::Rectangle(offsetX , offsetY + 1, GHOST_ZONE_WIDTH + 1, 1, Arcade::Colors::CYAN));
    display.draw(Arcade::Shapes::Rectangle(offsetX , offsetY + 1, 1, GHOST_ZONE_HEIGHT + 1, Arcade::Colors::CYAN));
    display.draw(Arcade::Shapes::Rectangle(offsetX + 1, offsetY + GHOST_ZONE_HEIGHT + 1, GHOST_ZONE_WIDTH + 1, 0, Arcade::Colors::CYAN));
    display.draw(Arcade::Shapes::Rectangle(offsetX + GHOST_ZONE_WIDTH + 1, offsetY + 1, 0, GHOST_ZONE_HEIGHT + 1, Arcade::Colors::CYAN));
    display.draw(Arcade::Shapes::Rectangle(0, 0, MAP_WIDTH + 2, 0, Arcade::Colors::BLUE));
    display.draw(Arcade::Shapes::Rectangle(0, 0, 0, MAP_HEIGHT + 2, Arcade::Colors::BLUE));
    display.draw(Arcade::Shapes::Rectangle(0, MAP_HEIGHT + 1, MAP_WIDTH + 2, 0, Arcade::Colors::BLUE));
    display.draw(Arcade::Shapes::Rectangle(MAP_WIDTH + 1, 0, 0, MAP_HEIGHT + 2, Arcade::Colors::BLUE));
}

Color PacMan::getCellColor(Tools::CellType type)
{
    switch (type)
    {
        case Tools::GHOST: return _superPac ? Colors::GREEN : Colors::RED;
        case Tools::HEAD: return _superPac ? Colors::PURPLE : Colors::YELLOW;
        case Tools::WALL: return Colors::BLUE;
        case Tools::GATE: return Colors::PURPLE;
        case Tools::PACGUN: return Colors::YELLOW;
        case Tools::EMPTY: return Colors::BLACK;
        default: return Colors::BLACK;
    }
}

}

extern "C" Arcade::IGame* get_game()
{
    return new Arcade::PacMan();
}
