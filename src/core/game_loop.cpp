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

void game_loop(Arcade::IDisplay& display, Arcade::IGame& game, Arcade::Player& player)
{
    auto last = std::chrono::steady_clock::now();
    constexpr std::chrono::nanoseconds FRAME_TIME{16'666'667}; // ~60 FPS cap

    while (display.isOpen()) {
        if (auto evt = display.pollEvent()) {
            if (*evt == Arcade::Events::ARC_KEY_ESC || *evt == Arcade::Events::ARC_CLOSE) {
                break;
            }
            game.handleEvent(*evt, display);
        }

        auto now = std::chrono::steady_clock::now();
        auto dt = now - last;
        last = now;

        game.update(dt, player);

        display.clear();
        game.render(display);
        display.display();

        auto frameEnd = std::chrono::steady_clock::now();
        auto frameDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(frameEnd - now);
        auto sleepTime = std::max(0ns, FRAME_TIME - frameDuration);
        std::this_thread::sleep_for(sleepTime);
    }
}
