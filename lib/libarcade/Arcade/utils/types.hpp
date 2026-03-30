/*
** EPITECH PROJECT, 2026
** Project - Arcade
** File description:
** Header file for
** libarcade's typedefs
*/

#pragma once

#include <cstdint>


namespace Arcade {
    class IGame;
    class IDisplay;

    inline namespace Types {
        using Coordinate = std::int_fast16_t;
        using Distance = std::uint_fast16_t;   // a distance can't be negative

        // Entry points
        using GameEntryPointFnc = IGame*(*)();
        using DisplayEntryPointFnc = IDisplay*(*)();
    }
}
