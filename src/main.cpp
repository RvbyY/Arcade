#include <dlfcn.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"
#include "tools/grid.hpp"

int main(int argc, char* argv[])
{
    const char* displayPath = argc >= 2 ? argv[1] : "";
    const char* gamePath = argc >= 3 ? argv[2] : "lib/arcade_snake.so"; // default to snake for testing

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_graphic_lib> [path_to_game_lib]" << std::endl;
        return 1;
    }

    // load display lib
    void* displayHandle = dlopen(displayPath, RTLD_NOW);
    if (!displayHandle) {
        std::cerr << dlerror() << std::endl;
        return 1;
    }

    auto createDisplay = reinterpret_cast<Arcade::DisplayEntryPointFnc>(::dlsym(displayHandle, Arcade::DISPLAY_ENTRYPOINT));
    if (!createDisplay) {
        std::cerr << "Not a graphic library." << std::endl;
        dlclose(displayHandle);
        return 1;
    }

    // load game lib (snake by default)
    void* gameHandle = dlopen(gamePath, RTLD_NOW);
    if (!gameHandle) {
        std::cerr << dlerror() << std::endl;
        dlclose(displayHandle);
        return 1;
    }
    auto createGame = reinterpret_cast<Arcade::GameEntryPointFnc>(::dlsym(gameHandle, Arcade::GAME_ENTRYPOINT));
    if (!createGame) {
        std::cerr << "Not a game library." << std::endl;
        dlclose(gameHandle);
        dlclose(displayHandle);
        return 1;
    }

    Arcade::IDisplay* display = createDisplay();
    Arcade::IGame* game = createGame();
    Arcade::Player player(std::string("tester"));

    display->open();
    game->init();

    auto last = std::chrono::steady_clock::now();
    constexpr std::chrono::nanoseconds FRAME_TIME{16'666'667}; // ~60 FPS cap
    while (display->isOpen()) {
        // handle events
        if (auto evt = display->pollEvent()) {
            if (*evt == Arcade::Events::ARC_KEY_ESC || *evt == Arcade::Events::ARC_CLOSE) {
                break;
            }
            game->handleEvent(*evt, *display);
        }

        auto now = std::chrono::steady_clock::now();
        auto dt = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last);
        last = now;

        game->update(dt, player);

        display->clear();
        game->render(*display);
        display->display();

        auto frameEnd = std::chrono::steady_clock::now();
        auto frameDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(frameEnd - now);
        if (frameDuration < FRAME_TIME)
            std::this_thread::sleep_for(FRAME_TIME - frameDuration);
    }

    game->destroy();
    display->close();

    delete game;
    delete display;

    dlclose(gameHandle);
    dlclose(displayHandle);
    return 0;
}
