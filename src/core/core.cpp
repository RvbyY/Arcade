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

int core(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_graphic_lib> [path_to_game_lib]" << std::endl;
        return 1;
    }

    const char* displayPath = argv[1];
    const char* gamePath = argc >= 3 ? argv[2] : "lib/arcade_snake.so"; // default to snake for testing

    SharedLibrary displayHandle = load_library_or_throw(displayPath);
    Arcade::DisplayEntryPointFnc createDisplay = load_display_entrypoint_or_throw(displayHandle.get());

    SharedLibrary gameHandle = load_library_or_throw(gamePath);
    Arcade::GameEntryPointFnc createGame = load_game_entrypoint_or_throw(gameHandle.get());

    std::unique_ptr<Arcade::IDisplay> display(createDisplay());
    std::unique_ptr<Arcade::IGame> game(createGame());
    Arcade::Player player(std::string("tester"));

    bool displayOpened = false;
    bool gameInitialized = false;
    try {
        display->open();
        displayOpened = true;
        game->init();
        gameInitialized = true;
        game_loop(*display, *game, player);
    } catch (...) {
        if (gameInitialized) {
            game->destroy();
        }
        if (displayOpened) {
            display->close();
        }
        throw;
    }

    game->destroy();
    display->close();
    return 0;
}
