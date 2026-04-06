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

int core(int argc, char* argv[]);
void game_loop(Arcade::IDisplay& display, Arcade::IGame& game, Arcade::Player& player);

void close_library(void* handle);

using SharedLibrary = std::unique_ptr<void, void(*)(void*)>;

SharedLibrary load_library_or_throw(const char* path);
Arcade::DisplayEntryPointFnc load_display_entrypoint_or_throw(void* displayHandle);
Arcade::GameEntryPointFnc load_game_entrypoint_or_throw(void* gameHandle);
