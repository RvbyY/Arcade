/*
** EPITECH PROJECT, 2026
** Project - Arcade
** File description:
** Header file for
** Player struct
*/

#pragma once

#include <string_view>
#include <cstdint>
#include <string>


namespace Arcade {
    /**
     * Libraries may extend this
     * struct by inheriting from it,
     * as long as you don't change
     * IGame::update()'s parameter AND
     * don't dynamic_cast<>() to your
     * subclass in the update function.
     */
    struct Player {
        std::string name;
        std::uint64_t score;

        Player(std::string_view name) : name(name), score(0) {}

        constexpr bool operator==(const Player& other) const { return name == other.name; }
    };
}

template <>
struct std::hash<Arcade::Player>
{
    /**
     * Note: we only use the player's name
     * when hashing, as the score is irrelevant.
     */
    std::size_t operator()(const Arcade::Player& player) const noexcept
    {
        return std::hash<std::string>{}(player.name);
    }
};
