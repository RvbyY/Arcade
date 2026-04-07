/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** load
*/

#include <dlfcn.h>
#include <stdexcept>
#include "core/core.hpp"

void Core::closeLibrary(void* handle)
{
    if (handle != nullptr) {
        dlclose(handle);
    }
}

Core::SharedLibrary Core::loadLibraryOrThrow(const char* path)
{
    SharedLibrary handle(dlopen(path, RTLD_NOW), &closeLibrary);

    if (!handle) {
        throw std::runtime_error(dlerror());
    }
    return handle;
}

Arcade::DisplayEntryPointFnc Core::loadDisplayEntryPointOrThrow(void* displayHandle)
{
    auto createDisplay = reinterpret_cast<Arcade::DisplayEntryPointFnc>(::dlsym(displayHandle, Arcade::DISPLAY_ENTRYPOINT));

    if (!createDisplay) {
        throw std::runtime_error("Not a graphic library.");
    }
    return createDisplay;
}

Arcade::GameEntryPointFnc Core::loadGameEntryPointOrThrow(void* gameHandle)
{
    auto createGame = reinterpret_cast<Arcade::GameEntryPointFnc>(::dlsym(gameHandle, Arcade::GAME_ENTRYPOINT));

    if (!createGame) {
        throw std::runtime_error("Not a game library.");
    }
    return createGame;
}
