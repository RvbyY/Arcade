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
    void run();

    private:
    std::span<char *> _args;
    Arcade::IDisplay* _currDisplay;
    Arcade::IGame* _currGame;
    Arcade::Player* _currPlayer;

    std::vector<std::unique_ptr<Arcade::IDisplay>> _displays;
    std::vector<std::unique_ptr<Arcade::IGame>> _games;
    std::vector<std::unique_ptr<Arcade::Player>> _players;

    void game_loop();
    static void closeLibrary(void* handle);
    static SharedLibrary loadLibraryOrThrow(const char* path);
    static Arcade::DisplayEntryPointFnc loadDisplayEntryPointOrThrow(void* displayHandle);
    static Arcade::GameEntryPointFnc loadGameEntryPointOrThrow(void* gameHandle);





};