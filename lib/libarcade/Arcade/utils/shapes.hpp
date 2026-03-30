/*
** EPITECH PROJECT, 2026
** Project - Arcade
** File description:
** Header file for
** Everything related
** to shapes
*/

#pragma once

#include "colors.hpp"
#include "types.hpp"


namespace Arcade::Shapes {
    /**
     * The shape designating
     * a point.
     *
     * Note:
     * Unlike mathematical points,
     * these points actually have
     * a width and height (as
     * determined by the display's
     * cell size.
     */
    struct Point {
        Coordinate x;
        Coordinate y;
        Color color;

        constexpr Point() noexcept : Point(0, 0) {}

        constexpr Point(Coordinate x, Coordinate y, Color color = 0x0) noexcept
            : x(x), y(y)
            , color(color)
        {}
    };

    /**
     * The shape designating a
     * rectangle.
     *
     * Setting either the width
     * or the height to 0 should
     * produce a vertical or
     * horizontal line respectively.
     *
     * Setting both the width and
     * height to 0 will produce the
     * same thing as a Point.
     */
    struct Rectangle {
        Coordinate x;
        Coordinate y;
        Distance width;
        Distance height;
        Color color;

        constexpr Rectangle() noexcept : Rectangle(0, 0, 0, 0) {}

        constexpr Rectangle(
            Coordinate x, Coordinate y,
            Distance w, Distance h,
            Color c = 0x0
        ) noexcept
            : x(x), y(y)
            , width(w), height(h)
            , color(c)
        {}
    };
}
