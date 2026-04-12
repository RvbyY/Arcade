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
    if (!(Arcade::Events::ARC_KEY_F1 <= evt && evt <= Arcade::Events::ARC_KEY_F12))
        return std::nullopt;

    return evt - Arcade::Events::ARC_KEY_F1;
}
}

bool Core::handleGlobalEvent(Arcade::Events::Event evt)
{
    if (const auto displayIndex = getDisplayShortcutIndex(evt)) {
        selectDisplay(*displayIndex);
        return true;
    }
    if (evt == Arcade::Events::ARC_KEY_TAB) {
        toggleLeaderboardVisibility();
        return true;
    }
    if (!isLoadedGameActive()) {
        return false;
    }
    switch (evt) {
        case Arcade::Events::ARC_KEY_L:
            cycleToNextDisplay();
            return true;
        case Arcade::Events::ARC_KEY_G:
            cycleToNextGame();
            return true;
        case Arcade::Events::ARC_KEY_M:
            switchToSelectMenu();
            return true;
        default:
            return false;
    }
}

bool Core::pollCoreEvents()
{
    while (auto evt = _currDisplay->pollEvent()) {
        if (*evt == Arcade::Events::ARC_CLOSE) {
            return false;
        }
        if (*evt == Arcade::Events::ARC_KEY_ESC) {
            if (_currGame == &_selectMenu) {
                switchToUserInputMenu();
                applyPendingGameSwitch();
                return true;
            }
            return false;
        }
        if (*evt == Arcade::Event::ARC_KEY_P && _currGame != &_userInputMenu)
            _debugOverlay = _debugOverlay ? std::nullopt : std::make_optional(Arcade::DebugOverlay(*this));
        if (handleGlobalEvent(*evt)) {
            applyPendingGameSwitch();
        } else {
            _currGame->handleEvent(*evt, *_currDisplay);
        }
    }
    return true;
}

int Core::game_loop()
{
    auto last = std::chrono::steady_clock::now();
    constexpr std::chrono::nanoseconds FRAME_TIME{16'666'667}; // ~60 FPS cap

    while (_currDisplay->isOpen()) {
        if (pollCoreEvents() == false)
            break;
        auto now = std::chrono::steady_clock::now();
        auto dt = now - last;
        last = now;

        _currGame->update(dt, *_currPlayer);
        applyPendingGameSwitch();

        _currDisplay->clear();
        _currGame->render(*_currDisplay);
        if (_leaderboardVisible) {
            _leaderboardOverlay.render(*_currDisplay);
        }
        if (_debugOverlay) {
            _debugOverlay->render(*_currDisplay);
        }
        _currDisplay->display();


        auto frameEnd = std::chrono::steady_clock::now();
        auto frameDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(frameEnd - now);
        auto sleepTime = std::max(0ns, FRAME_TIME - frameDuration);
        std::this_thread::sleep_for(sleepTime);
    }
    return 0;
}

void Core::updatePlayerScore()
{
    // check si le joueur a déjà un score enregistré dans le futur fichier
    // et si oui, si son nouveau score est meilleur on l'enregistree
    _currPlayer->maxScore = std::max(_currPlayer->maxScore, _currPlayer->score);
    _currPlayer->score = 0;
    _players.save();
}

void Core::applyPendingGameSwitch()
{
    if (_pendingGame == nullptr || _pendingGame == _currGame) {
        _pendingGame = nullptr;
        return;
    }
    _currGame->destroy();
    updatePlayerScore();
    _currGame = _pendingGame;
    _pendingGame = nullptr;
    _currGame->init();
}
