/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** game_loop
*/

#include <algorithm>
#include <chrono>
#include <thread>
#include "core/core.hpp"

using std::chrono_literals::operator ""ns;

int Core::game_loop()
{
    auto last = std::chrono::steady_clock::now();
    constexpr std::chrono::nanoseconds FRAME_TIME{16'666'667}; // ~60 FPS cap

    while (_currDisplay->isOpen()) {
        if (auto evt = _currDisplay->pollEvent()) {
            if (*evt == Arcade::Events::ARC_KEY_ESC || *evt == Arcade::Events::ARC_CLOSE) {
                break;
            }
            _currGame->handleEvent(*evt, *_currDisplay);
        }

        auto now = std::chrono::steady_clock::now();
        auto dt = now - last;
        last = now;

        _currGame->update(dt, *_currPlayer);

        _currDisplay->clear();
        _currGame->render(*_currDisplay);
        _currDisplay->display();

        auto frameEnd = std::chrono::steady_clock::now();
        auto frameDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(frameEnd - now);
        auto sleepTime = std::max(0ns, FRAME_TIME - frameDuration);
        std::this_thread::sleep_for(sleepTime);
    }
    return 0;
}
