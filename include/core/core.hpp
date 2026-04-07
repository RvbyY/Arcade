/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** core
*/

#pragma once

#include <memory>
#include "Arcade/display.hpp"
#include "Arcade/game.hpp"
#include "Arcade/utils.hpp"

class Core {
    public:
    using SharedLibrary = std::unique_ptr<void, void(*)(void*)>;
    Core(int argc, char** argv);
    int run();

    private:
    std::span<char *> _args;
    Arcade::IDisplay* _currDisplay = nullptr;
    Arcade::IGame* _currGame = nullptr;
    Arcade::Player* _currPlayer = nullptr;

    std::vector<SharedLibrary> _displayHandles;
    std::vector<SharedLibrary> _gameHandles;

    std::vector<std::unique_ptr<Arcade::IDisplay>> _displays;
    std::vector<std::unique_ptr<Arcade::IGame>> _games;
    std::vector<std::unique_ptr<Arcade::Player>> _players;

    int game_loop();
    static void closeLibrary(void* handle);
    static SharedLibrary loadLibraryOrThrow(const char* path);
    static Arcade::DisplayEntryPointFnc loadDisplayEntryPointOrThrow(void* displayHandle);
    static Arcade::GameEntryPointFnc loadGameEntryPointOrThrow(void* gameHandle);





};
