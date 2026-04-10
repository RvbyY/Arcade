/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** load
*/

#include <dlfcn.h>
#include <algorithm>
#include <filesystem>
#include <optional>
#include <stdexcept>
#include <vector>
#include "core/core.hpp"

namespace {
std::optional<Arcade::DisplayEntryPointFnc> tryLoadDisplayEntryPoint(void* displayHandle)
{
    auto createDisplay = reinterpret_cast<Arcade::DisplayEntryPointFnc>(::dlsym(displayHandle, Arcade::DISPLAY_ENTRYPOINT));

    if (!createDisplay) {
        return std::nullopt;
    }
    return createDisplay;
}

std::optional<Arcade::GameEntryPointFnc> tryLoadGameEntryPoint(void* gameHandle)
{
    auto createGame = reinterpret_cast<Arcade::GameEntryPointFnc>(::dlsym(gameHandle, Arcade::GAME_ENTRYPOINT));

    if (!createGame) {
        return std::nullopt;
    }
    return createGame;
}

std::optional<std::size_t> findPreferredIndex(const std::vector<std::string>& paths, std::string_view preferredPath)
{
    namespace fs = std::filesystem;

    if (preferredPath.empty()) {
        return std::nullopt;
    }

    const fs::path preferred(preferredPath);
    for (std::size_t i = 0; i < paths.size(); ++i) {
        const fs::path candidate(paths[i]);

        if (candidate == preferred || candidate.filename() == preferred.filename()) {
            return i;
        }
    }
    return std::nullopt;
}
}

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

void Core::loadLibrariesFromDirectory(std::string_view directory)
{
    std::vector<std::filesystem::path> libraryPaths;
    const std::filesystem::path libraryDirectory(directory);

    if (!std::filesystem::exists(libraryDirectory)) {
        throw std::runtime_error("Missing lib/ directory.");
    }

    for (const auto& entry : std::filesystem::directory_iterator(libraryDirectory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".so") {
            libraryPaths.push_back(entry.path());
        }
    }
    std::sort(libraryPaths.begin(), libraryPaths.end());

    for (const auto& libraryPath : libraryPaths) {
        try {
            SharedLibrary handle = loadLibraryOrThrow(libraryPath.c_str());

            if (const auto createDisplay = tryLoadDisplayEntryPoint(handle.get())) {
                if (Arcade::IDisplay* display = (*createDisplay)()) {
                    _displayPaths.push_back(libraryPath.string());
                    _displayHandles.push_back(std::move(handle));
                    _displays.emplace_back(display);
                    continue;
                }
            }

            if (const auto createGame = tryLoadGameEntryPoint(handle.get())) {
                if (Arcade::IGame* game = (*createGame)()) {
                    _gamePaths.push_back(libraryPath.string());
                    _gameHandles.push_back(std::move(handle));
                    _games.emplace_back(game);
                }
            }
        } catch (const std::exception&) {
            // ajouter un message de warning pour indiquer que la lib en question a pas load
            continue;
        }
    }
}

void Core::selectInitialLibraries(std::string_view preferredDisplayPath, std::string_view preferredGamePath)
{
    if (const auto displayIndex = findPreferredIndex(_displayPaths, preferredDisplayPath)) {
        _selectedDisplayIndex = *displayIndex;
    } else {
        throw std::runtime_error("Invalid graphical library path provided: " + std::string(preferredDisplayPath));
    }
    if (const auto gameIndex = findPreferredIndex(_gamePaths, preferredGamePath)) {
        _selectedGameIndex = *gameIndex;
    }
}
