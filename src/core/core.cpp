/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** core
*/

#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include "core/core.hpp"

Core::Core(int argc, char** argv)
    : _args(argv, argc)
    , _userInputMenu(*this)
    , _selectMenu(*this)
    , _leaderboardOverlay(*this)
    , _debugOverlay()
    , _selectedDisplayIndex(0)
    , _selectedGameIndex(0)
{
    _players.load();
}

static void printUsage()
{
    std::cout << "Usage: ./arcade <path_to_graphic_lib> [path_to_game_lib]" << std::endl << std::endl;
    std::cout << "The action keys are as follows:" << std::endl << std::endl;

    std::cout << "*In-game*" << std::endl;
    std::cout << "  ESC       -> Quit the game" << std::endl;
    std::cout << "  M         -> Return to the menu" << std::endl;
    std::cout << "  G         -> Switch to the next game" << std::endl;
    std::cout << "  L         -> Switch to the next graphical library" << std::endl;
    std::cout << "  R         -> Restart the current game" << std::endl;
    std::cout << "  F1...F12  -> Select a graphical library" << std::endl << std::endl;

    std::cout << "*Select Menu*" << std::endl;
    std::cout << "  ESC       -> Go back to the username input menu" << std::endl;
    std::cout << "  ENTER     -> Start the selected game" << std::endl << std::endl;

    std::cout << "*Username Input Menu*" << std::endl;
    std::cout << "  ESC       -> Exit the program" << std::endl;
    std::cout << "  ENTER     -> Confirm username and load the Selection Menu (requires at least one character)" << std::endl << std::endl;

    std::cout << "*Utils*" << std::endl;
    std::cout << "  TAB       -> Toggle leaderboard overlay" << std::endl;
    std::cout << "  P         -> Toggle debug overlay (shows current libraries)" << std::endl;
}

int Core::run()
{
    if (_args.size() < 2) {
        throw std::runtime_error("Usage: ./arcade <path_to_graphic_lib> [path_to_game_lib]");
    }
    if (std::string_view(_args[1]) == "-h" || std::string_view(_args[1]) == "--help") {
        printUsage();
        return 0;
    }
    const std::string_view preferredDisplayPath = _args[1];
    const std::string_view preferredGamePath = _args.size() >= 3 ? std::string_view(_args[2]) : std::string_view{};

    loadLibrariesFromDirectory("lib");
    if (_displays.empty()) {
        throw std::runtime_error("No display library found in lib/.");
    }
    if (_games.empty()) {
        throw std::runtime_error("No game library found in lib/.");
    }
    selectInitialLibraries(preferredDisplayPath, preferredGamePath);

    _currDisplay = _displays[_selectedDisplayIndex].get();
    _currGame = &_userInputMenu;

    bool displayOpened = false;
    bool gameInitialized = false;
    int status = 0;
    try {
        _currDisplay->open();
        displayOpened = true;
        _currGame->init();
        gameInitialized = true;
        status = game_loop();
    } catch (...) {
        if (gameInitialized) {
            _currGame->destroy();
        }
        if (displayOpened) {
            _currDisplay->close();
        }
        throw;
    }

    _currGame->destroy();
    _currDisplay->close();
    return status;
}

void Core::switchToUserInputMenu()
{
    setLeaderboardVisible(true);
    queueGameSwitch(&_userInputMenu);
}

void Core::switchToSelectMenu()
{
    setLeaderboardVisible(true);
    queueGameSwitch(&_selectMenu);
}

void Core::switchToLoadedGame()
{
    if (!_games.empty()) {
        queueGameSwitch(_games[_selectedGameIndex].get());
    }
}

void Core::cycleToNextDisplay()
{
    if (_displays.empty()) {
        return;
    }
    selectDisplay((_selectedDisplayIndex + 1) % _displays.size());
}

void Core::cycleToNextGame()
{
    if (_games.empty()) {
        return;
    }
    _selectedGameIndex = (_selectedGameIndex + 1) % _games.size();
    switchToLoadedGame();
}

bool Core::selectDisplay(std::size_t index)
{
    if (index >= _displays.size()) {
        return false;
    }

    if (_currDisplay == nullptr) {
        _selectedDisplayIndex = index;
        _currDisplay = _displays[index].get();
        return true;
    }

    if (_selectedDisplayIndex == index) {
        return true;
    }

    const bool wasOpen = _currDisplay->isOpen();
    if (wasOpen) {
        _currDisplay->close();
    }

    Arcade::DisplayEntryPointFnc createDisplay = loadDisplayEntryPointOrThrow(_displayHandles[index].get());
    _displays[index].reset(createDisplay());
    _selectedDisplayIndex = index;
    _currDisplay = _displays[index].get();

    if (wasOpen) {
        _currDisplay->open();
    }
    return true;
}

bool Core::selectGame(std::size_t index) noexcept
{
    if (index >= _games.size()) {
        return false;
    }
    _selectedGameIndex = index;
    return true;
}

Arcade::Player& Core::getCurrentPlayer() noexcept
{
    return *_currPlayer;
}

const Arcade::Player& Core::getCurrentPlayer() const noexcept
{
    return *_currPlayer;
}

const PlayerContainer& Core::players() const noexcept
{
    return _players;
}

std::size_t Core::displayCount() const noexcept
{
    return _displays.size();
}

std::size_t Core::gameCount() const noexcept
{
    return _games.size();
}

std::size_t Core::getSelectedDisplayIndex() const noexcept
{
    return _selectedDisplayIndex;
}

std::size_t Core::getSelectedGameIndex() const noexcept
{
    return _selectedGameIndex;
}

std::string_view Core::displayName(std::size_t index) const noexcept
{
    if (index >= _displays.size()) {
        return {};
    }
    return _displays[index]->libraryName();
}

std::string_view Core::gameTitle(std::size_t index) const noexcept
{
    if (index >= _games.size()) {
        return {};
    }
    return _games[index]->gameTitle();
}

bool Core::isLoadedGameActive() const noexcept
{
    return _currGame != nullptr && _currGame != &_userInputMenu && _currGame != &_selectMenu;
}

void Core::setLeaderboardVisible(bool visible) noexcept
{
    _leaderboardVisible = visible;
}

void Core::toggleLeaderboardVisibility() noexcept
{
    _leaderboardVisible = !_leaderboardVisible;
}

void Core::queueGameSwitch(Arcade::IGame* nextGame)
{
    if (nextGame != nullptr) {
        _pendingGame = nextGame;
    }
}
