/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** core
*/

#pragma once

#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <vector>
#include "Arcade/display.hpp"
#include "Arcade/game.hpp"
#include "Arcade/utils.hpp"
#include "../menu/selectMenu.hpp"
#include "../menu/userInputMenu.hpp"
#include "overlays/debugOverlay.hpp"
#include "playerContainer/playerContainer.hpp"


class Core {
    public:
    using SharedLibrary = std::unique_ptr<void, void(*)(void*)>;
    Core(int argc, char** argv);
    int run();

    void switchToUserInputMenu();
    void switchToSelectMenu();
    void switchToLoadedGame();
    void cycleToNextGame();
    bool selectDisplay(std::size_t index);
    bool selectGame(std::size_t index) noexcept;

    inline void setPlayer(const std::string& name) { _currPlayer = &_players[name]; }

    bool confirmCurrentPlayerSelection();

    Arcade::Player& getCurrentPlayer() noexcept;
    const Arcade::Player& getCurrentPlayer() const noexcept;

    std::size_t displayCount() const noexcept;
    std::size_t gameCount() const noexcept;

    std::size_t getSelectedDisplayIndex() const noexcept;
    std::size_t getSelectedGameIndex() const noexcept;

    std::string_view displayName(std::size_t index) const noexcept;
    std::string_view displayName() const noexcept { return _currDisplay->libraryName(); }
    std::string_view gameTitle(std::size_t index) const noexcept;
    inline std::string_view gameTitle() const noexcept { return _currGame->gameTitle(); }


    bool isLoadedGameActive() const noexcept;

    private:
    int game_loop();
    void loadLibrariesFromDirectory(std::string_view directory);
    void selectInitialLibraries(std::string_view preferredDisplayPath, std::string_view preferredGamePath);
    Arcade::Player* findPlayerByName(std::string_view name) const noexcept;
    void queueGameSwitch(Arcade::IGame* nextGame);
    void applyPendingGameSwitch();
    static void closeLibrary(void* handle);
    static SharedLibrary loadLibraryOrThrow(const char* path);
    static Arcade::DisplayEntryPointFnc loadDisplayEntryPointOrThrow(void* displayHandle);
    static Arcade::GameEntryPointFnc loadGameEntryPointOrThrow(void* gameHandle);

    bool handleGlobalEvent(Arcade::Events::Event evt);
    bool pollCoreEvents();

    void updatePlayerScore();

    std::span<char *> _args;
    Arcade::IDisplay* _currDisplay = nullptr;
    Arcade::IGame* _currGame = nullptr;
    Arcade::IGame* _pendingGame = nullptr;
    CorePlayer* _currPlayer = nullptr;

    std::vector<SharedLibrary> _displayHandles;
    std::vector<SharedLibrary> _gameHandles;

    std::vector<std::unique_ptr<Arcade::IDisplay>> _displays;
    std::vector<std::unique_ptr<Arcade::IGame>> _games;
    PlayerContainer _players;
    std::vector<std::string> _displayPaths;
    std::vector<std::string> _gamePaths;
    Arcade::Player _inputPlayer{""};

    std::size_t _selectedDisplayIndex = 0;
    std::size_t _selectedGameIndex = 0;

    Arcade::UserInputMenu _userInputMenu;
    Arcade::SelectMenu _selectMenu;

    std::optional<Arcade::DebugOverlay> _debugOverlay;
};
