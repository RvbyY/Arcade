/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** debugOverlay
*/

#pragma once

#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"

class Core;

namespace Arcade {
    class IDisplay;
    struct Player;

    class DebugOverlay : public IGame {
        public:
            DebugOverlay(Core& core);
            ~DebugOverlay() noexcept override = default;

            void init() override;
            void destroy() override;
            void handleEvent(Events::Event evt, IDisplay& display) override;
            void update(std::chrono::nanoseconds dt, Player& player) override;
            void render(IDisplay& display) override;

            std::string_view gameTitle() const noexcept override { return "Debug Overlay - BAM"; }

        private:
            Core& _core;
    };
}