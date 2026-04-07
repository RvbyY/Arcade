/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** game_loop
*/

#include <algorithm>
#include <chrono>
#include <optional>
#include <thread>
#include "core/core.hpp"

using std::chrono_literals::operator ""ns;

namespace {
std::optional<std::size_t> getDisplayShortcutIndex(Arcade::Events::Event evt)
{
    switch (evt) {
        case Arcade::Events::ARC_KEY_F1: return 0;
        case Arcade::Events::ARC_KEY_F2: return 1;
        case Arcade::Events::ARC_KEY_F3: return 2;
        case Arcade::Events::ARC_KEY_F4: return 3;
        case Arcade::Events::ARC_KEY_F5: return 4;
        case Arcade::Events::ARC_KEY_F6: return 5;
        case Arcade::Events::ARC_KEY_F7: return 6;
        case Arcade::Events::ARC_KEY_F8: return 7;
        case Arcade::Events::ARC_KEY_F9: return 8;
        case Arcade::Events::ARC_KEY_F10: return 9;
        case Arcade::Events::ARC_KEY_F11: return 10;
        case Arcade::Events::ARC_KEY_F12: return 11;

        default: return std::nullopt;
    }
}

bool handleGlobalEvent(Core& core, Arcade::Events::Event evt)
{
    if (const auto displayIndex = getDisplayShortcutIndex(evt)) {
        core.selectDisplay(*displayIndex);
        return true;
    }
    if (!core.isLoadedGameActive()) {
        return false;
    }
    switch (evt) {
        case Arcade::Events::ARC_KEY_G:
            core.cycleToNextGame();
            return true;
        case Arcade::Events::ARC_KEY_M:
            core.switchToSelectMenu();
            return true;
        default:
            return false;
    }
}
}

int Core::game_loop()
{
    auto last = std::chrono::steady_clock::now();
    constexpr std::chrono::nanoseconds FRAME_TIME{16'666'667}; // ~60 FPS cap

    while (_currDisplay->isOpen()) {
        if (auto evt = _currDisplay->pollEvent()) {
            if (*evt == Arcade::Events::ARC_CLOSE) {
                break;
            }
            if (*evt == Arcade::Events::ARC_KEY_ESC) {
                if (_currGame == &_selectMenu) {
                    switchToUserInputMenu();
                    applyPendingGameSwitch();
                    continue;
                }
                break;
            }
            if (handleGlobalEvent(*this, *evt)) {
                applyPendingGameSwitch();
            } else {
                _currGame->handleEvent(*evt, *_currDisplay);
            }
        }

        auto now = std::chrono::steady_clock::now();
        auto dt = now - last;
        last = now;

        _currGame->update(dt, *_currPlayer);
        applyPendingGameSwitch();

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

void Core::applyPendingGameSwitch()
{
    if (_pendingGame == nullptr || _pendingGame == _currGame) {
        _pendingGame = nullptr;
        return;
    }
    _currGame->destroy();
    _currGame = _pendingGame;
    _pendingGame = nullptr;
    _currGame->init();
}
