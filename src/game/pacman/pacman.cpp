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

std::optional<Tools::Vec2> PacMan::getRandomGumCoord()
{
    std::uniform_int_distribution<Arcade::Coordinate> distX(0, MAP_WIDTH - 1);
    std::uniform_int_distribution<Arcade::Coordinate> distY(0, MAP_HEIGHT - 1);
    Tools::Vec2 coords = {distX(_rng), distY(_rng)};

    for (size_t i = 0; i < GUN_MAX_ATTEMPs; i++) {
        if (_grid.getPosition(coords) == Tools::GUMS)
            return coords;
        coords = {distX(_rng), distY(_rng)};
    }
    return {};
}

void PacMan::setPacmanPosition()
{
    auto coords = getRandomGumCoord();
    if (coords) {
        _pacman = *coords;
    } else {
        _pacman = {MAP_WIDTH / 2, MAP_HEIGHT / 2};
    }
    _dir = Tools::Direction::RIGHT;
}

void PacMan::setGhostsPositions()
{
    int offsetX = GHOST_ZONE_CENTER_X - GHOST_ZONE_WIDTH / 2;
    int offsetY = GHOST_ZONE_CENTER_Y - GHOST_ZONE_HEIGHT / 2;

    for (int i = 0; i < 4; i++) {
        _ghosts[i] = {offsetX + 2 + (i % 2), offsetY + 2 + (i / 2)};
    }
}

bool PacMan::spawnPacGun()
{
    if (_nbPacGun >= TARGET_GUN)
        return false;
    auto pacGunCoords = getRandomGumCoord();

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
    MOVE_DELAY = std::chrono::milliseconds(200);
    _gameScore += 10;
}

void PacMan::createMap(int randomValue, std::uniform_int_distribution<int> dist)
{
    int offsetX = GHOST_ZONE_CENTER_X - GHOST_ZONE_WIDTH / 2;
    int offsetY = GHOST_ZONE_CENTER_Y - GHOST_ZONE_HEIGHT / 2;
    int gateX = offsetX + GHOST_ZONE_WIDTH / 2;
    int gateY = offsetY;

    _grid.reset(Tools::GUMS);
    for (auto& cell : _grid.cells) {
        randomValue = dist(_rng);
        if (randomValue < 20)
            cell = Tools::WALL;
    }

    for (int y = offsetY; y <= offsetY + GHOST_ZONE_HEIGHT; y++) {
        for (int x = offsetX; x <= offsetX + GHOST_ZONE_WIDTH; x++) {
            bool isBorder = (x == offsetX || x == offsetX + GHOST_ZONE_WIDTH || y == offsetY || y == offsetY + GHOST_ZONE_HEIGHT);
            if (isBorder) {
                if (y == gateY && (x == gateX || x == gateX + 1))
                    _grid.setPosition({x, y}, Tools::GATE);
                else
                    _grid.setPosition({x, y}, Tools::WALL);
            } else {
                _grid.setPosition({x, y}, Tools::EMPTY);
            }
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
    _gameWon = false;
    _gameOver = false;
    _superPac = false;
    _superPacTimer = 0ns;
    for (int i = 0; i < 4; i++)
        _ghostFrozenUntil[i] = 0ns;
    createMap(randomValue, dist);
    PacMan::setPacmanPosition();
    PacMan::setGhostsPositions();
    for (size_t i = 0; i < TARGET_GUN; i++) {
        auto pacGunCoords = getRandomGumCoord();
        if (pacGunCoords) {
            _pacGuns.insert(*pacGunCoords);
            _nbPacGun++;
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
    _gameScore = 0;
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
        std::uniform_int_distribution<size_t> dist(0, validMoves.size());
        _ghosts[ghostIndex] = validMoves[dist(_rng)];
    }
}

void PacMan::eatGum(Tools::Vec2 nextCell)
{
    if (Tools::GUMS == _grid.getPosition(nextCell)) {
        _gameScore += 1;
        _grid.setPosition(nextCell, Tools::EMPTY);
    }
}

void PacMan::update(std::chrono::nanoseconds dt, Player& player)
{
    player.score = _gameScore;
    if (_gameOver || _gameWon)
        return;
    _superPacTimer += dt;
    _accumulator += dt;
    if (_accumulator < MOVE_DELAY)
        return;
    _accumulator -= MOVE_DELAY;

    auto nextCell = _grid.wrap(_pacman + _dir);
    if (_grid.getPosition(nextCell) != Tools::WALL && _grid.getPosition(nextCell) != Tools::GATE) {
        _pacman = nextCell;
    }

    eatGum(_pacman);
    if (_pacGuns.count(_pacman) > 0) {
        _pacGuns.erase(_pacman);
        eatPacGun(player);
        _superPacTimer = 0ns;
    }

    for (int i = 0; i < 4; i++) {
        if (_ghostFrozenUntil[i] < _superPacTimer)
            moveGhosts(i);
    }

    for (int i = 0; i < 4; i++) {
        if (_pacman == _ghosts[i]) {
            if (!_superPac) {
                _gameOver = true;
                return;
            }
            if (_superPac && _ghostFrozenUntil[i] < _superPacTimer) {
                _gameScore += 20;
                int offsetX = GHOST_ZONE_CENTER_X - GHOST_ZONE_WIDTH / 2;
                int offsetY = GHOST_ZONE_CENTER_Y - GHOST_ZONE_HEIGHT / 2;
                _ghosts[i] = {offsetX + 2 + (i % 2), offsetY + 2 + (i / 2)};
                _ghostFrozenUntil[i] = _superPacTimer + 10s;
            }
        }
    }

    if (_superPac && _superPacTimer > 10s) {
        _superPac = false;
        MOVE_DELAY = std::chrono::milliseconds(100);
    }
    if (_nbPacGun == 0)
        _gameWon = true;
}

void PacMan::render(IDisplay& display)
{
    int offsetX = GHOST_ZONE_CENTER_X - GHOST_ZONE_WIDTH / 2;
    int offsetY = GHOST_ZONE_CENTER_Y - GHOST_ZONE_HEIGHT / 2;
    auto drawEndDialog = [&](std::string_view title, Arcade::Color bannerColor) {
        constexpr std::string_view restartLabel = "PRESS R TO RESTART";
        const Arcade::Coordinate dialogWidth = 26;
        const Arcade::Coordinate dialogHeight = 4;
        const Arcade::Coordinate dialogX = (MAP_WIDTH + 2 - dialogWidth) / 2;
        const Arcade::Coordinate dialogY = (MAP_HEIGHT + 2 - dialogHeight) / 2;
        const Arcade::Coordinate titleX = dialogX + (dialogWidth - static_cast<Arcade::Coordinate>(title.size())) / 2;
        const Arcade::Coordinate restartX = dialogX + (dialogWidth - static_cast<Arcade::Coordinate>(restartLabel.size())) / 2;

        display.draw(Arcade::Shapes::Rectangle(dialogX, dialogY, dialogWidth, dialogHeight, Arcade::Colors::BLACK));
        display.draw(Arcade::Shapes::Rectangle(dialogX, dialogY, dialogWidth, 0, bannerColor));
        display.draw(Arcade::Shapes::Rectangle(dialogX, dialogY + dialogHeight, dialogWidth, 0, bannerColor));
        display.draw(Arcade::Shapes::Rectangle(dialogX, dialogY, 0, dialogHeight, bannerColor));
        display.draw(Arcade::Shapes::Rectangle(dialogX + dialogWidth, dialogY, 0, dialogHeight, bannerColor));
        display.draw(Arcade::Text(title, titleX, dialogY + 1, Arcade::Colors::WHITE));
        display.draw(Arcade::Text(restartLabel, restartX, dialogY + 2, bannerColor));
    };

    for (long x = 0; x < MAP_WIDTH + 2; x++)
        for (long y = 0; y < MAP_HEIGHT + 2; y++)
            display.draw(Arcade::Shapes::Point(x, y, Arcade::Colors::BLACK));
    for (long x = 0; x < MAP_WIDTH; x++)
        for (long y = 0; y < MAP_HEIGHT; ++y)
            display.draw(Arcade::Shapes::Point(x + 1, y + 1, getCellColor(_grid.getPosition({x, y}))));
    for (const auto& pacGun : _pacGuns)
        display.draw(Arcade::Shapes::Point(pacGun.x + 1, pacGun.y + 1, getCellColor(Tools::PACGUN)));
    for (const auto& ghostPos : _ghosts)
        display.draw(Arcade::Shapes::Point(ghostPos.x + 1, ghostPos.y + 1, getCellColor(Tools::GHOST)));
    display.draw(Arcade::Shapes::Point(_pacman.x + 1, _pacman.y + 1, getCellColor(Tools::HEAD)));
    display.draw(Arcade::Shapes::Rectangle(offsetX , offsetY + 1, GHOST_ZONE_WIDTH + 1, 1, Arcade::Colors::CYAN));
    display.draw(Arcade::Shapes::Rectangle(offsetX , offsetY + 1, 1, GHOST_ZONE_HEIGHT + 1, Arcade::Colors::CYAN));
    display.draw(Arcade::Shapes::Rectangle(offsetX + 1, offsetY + GHOST_ZONE_HEIGHT + 1, GHOST_ZONE_WIDTH + 1, 0, Arcade::Colors::CYAN));
    display.draw(Arcade::Shapes::Rectangle(offsetX + GHOST_ZONE_WIDTH + 1, offsetY + 1, 0, GHOST_ZONE_HEIGHT + 1, Arcade::Colors::CYAN));
    display.draw(Arcade::Shapes::Rectangle(0, 0, MAP_WIDTH + 2, 0, Arcade::Colors::BLUE));
    display.draw(Arcade::Shapes::Rectangle(0, 0, 0, MAP_HEIGHT + 2, Arcade::Colors::BLUE));
    display.draw(Arcade::Shapes::Rectangle(0, MAP_HEIGHT + 1, MAP_WIDTH + 2, 0, Arcade::Colors::BLUE));
    display.draw(Arcade::Shapes::Rectangle(MAP_WIDTH + 1, 0, 0, MAP_HEIGHT + 2, Arcade::Colors::BLUE));
    if (_gameOver)
        drawEndDialog("GAME OVER", Arcade::Colors::RED);
    else if (_gameWon)
        drawEndDialog("YOU WON", Arcade::Colors::GREEN);
}

Color PacMan::getCellColor(Tools::CellType type)
{
    switch (type)
    {
        case Tools::GHOST: return _superPac ? Colors::GREEN : Colors::RED;
        case Tools::HEAD: return _superPac ? Colors::PURPLE : Colors::YELLOW;
        case Tools::WALL: return Colors::BLUE;
        case Tools::GATE: return Colors::PURPLE;
        case Tools::PACGUN: return ORANGE;
        case Tools::EMPTY: return Colors::BLACK;
        case Tools::GUMS: return Colors::WHITE;
        default: return Colors::BLACK;
    }
}

}

extern "C" Arcade::IGame* get_game()
{
    return new Arcade::PacMan();
}
