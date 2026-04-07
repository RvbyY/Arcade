/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** core
*/

#include <iostream>
#include <memory>
#include <string>
#include "core/core.hpp"

Core::Core(int argc, char** argv)
    : _args(argv, argc)
{
}

int Core::run()
{
    if (_args.size() < 2) {
        throw std::runtime_error("Usage: ./arcade <path_to_graphic_lib> [path_to_game_lib]");
    }

    const auto& displayPath = _args[1];
    const char* gamePath = _args.size() >= 3 ? _args[2] : "lib/arcade_snake.so"; // default to snake for testing - change to menu

    _displayHandles.emplace_back(loadLibraryOrThrow(displayPath));
    Arcade::DisplayEntryPointFnc createDisplay = loadDisplayEntryPointOrThrow(_displayHandles.back().get());

    _gameHandles.emplace_back(loadLibraryOrThrow(gamePath));
    Arcade::GameEntryPointFnc createGame = loadGameEntryPointOrThrow(_gameHandles.back().get());

    _displays.emplace_back(createDisplay());
    _games.emplace_back(createGame());
    _players.push_back(std::make_unique<Arcade::Player>("nom"));

    _currDisplay = _displays[0].get();
    _currGame = _games[0].get();
    _currPlayer = _players[0].get();

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
