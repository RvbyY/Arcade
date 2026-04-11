/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** playerContainer
*/

#pragma once


#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"
#include <span>
#include <map>
#include <filesystem>

struct CorePlayer : Arcade::Player {
    CorePlayer() : Player(""), maxScore(0) {}

    decltype(Arcade::Player::score) maxScore = 0;
};

class PlayerContainer {
    public:
        PlayerContainer() noexcept = default;

        void save(const std::filesystem::path& path = DEFAULT_PATH);
        void load(const std::filesystem::path& path = DEFAULT_PATH);

        inline auto begin() { return _players.begin(); }
        inline auto begin() const { return _players.begin(); }
        inline auto cbegin() const { return _players.cbegin(); }

        inline auto end() { return _players.end(); }
        inline auto end() const { return _players.end(); }
        inline auto cend() const { return _players.cend(); }

        inline CorePlayer& operator[](const std::string& name)
        {
            CorePlayer& player = _players[name];

            if (player.name.empty())
                player.name = name;

            return player;
        }

    private:
        static constexpr std::string_view DEFAULT_PATH = "saves/player_scores.arc";
        std::map<std::string, CorePlayer> _players;
};
