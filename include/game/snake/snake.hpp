/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** snake
*/

#pragma once

#include <chrono>
#include <deque>
#include <optional>
#include <random>
#include <unordered_set>
#include "../lib/libarcade/Arcade/game.hpp"
#include "tools/grid.hpp"

namespace Arcade {
    class IDisplay;
    struct Player;

    class Snake : public IGame {
        public:
            Snake();
            ~Snake() noexcept override = default;

            void init() override;
            void destroy() override;
            void handleEvent(Events::Event evt, IDisplay& display) override;
            void update(std::chrono::nanoseconds dt, Player& player) override;
            void render(IDisplay& display) override;

            std::string_view gameTitle() const noexcept override { return "Snake - BAM"; }

        private:
            static constexpr int MAP_WIDTH = 20;
            static constexpr int MAP_HEIGHT = 20;
            static constexpr int TARGET_APPLES = 3;
            static constexpr size_t APPLE_ATTEMPTS_MAX = 100;
            static constexpr std::chrono::duration<double> MOVE_DELAY { 6.0 }; // configurable constant

            // helpers
            bool spawnApple();
            std::optional<Tools::Vec2> getRandomEmptyCoord();
            Arcade::Color getCellColor(Tools::CellType type);

            // state
            size_t nbApples;
            Tools::Grid<Tools::CellType> _grid;
            std::mt19937 _rng;
            std::deque<Tools::Vec2> _snake;               // front = head
            Tools::Direction _dir;
            std::chrono::nanoseconds _accumulator;
            bool _gameOver;
    };
}
