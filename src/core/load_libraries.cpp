/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** load
*/

#include <dlfcn.h>
#include <stdexcept>
#include "core/core.hpp"

void close_library(void* handle)
{
    if (handle != nullptr) {
        dlclose(handle);
    }
}

SharedLibrary load_library_or_throw(const char* path)
{
    SharedLibrary handle(dlopen(path, RTLD_NOW), &close_library);

    if (!handle) {
        throw std::runtime_error(dlerror());
    }
    return handle;
}

Arcade::DisplayEntryPointFnc load_display_entrypoint_or_throw(void* displayHandle)
{
    auto createDisplay = reinterpret_cast<Arcade::DisplayEntryPointFnc>(::dlsym(displayHandle, Arcade::DISPLAY_ENTRYPOINT));

    if (!createDisplay) {
        throw std::runtime_error("Not a graphic library.");
    }
    return createDisplay;
}

Arcade::GameEntryPointFnc load_game_entrypoint_or_throw(void* gameHandle)
{
    auto createGame = reinterpret_cast<Arcade::GameEntryPointFnc>(::dlsym(gameHandle, Arcade::GAME_ENTRYPOINT));

    if (!createGame) {
        throw std::runtime_error("Not a game library.");
    }
    return createGame;
}
