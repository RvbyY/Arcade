/*
** EPITECH PROJECT, 2026
** Project - Arcade
** File description:
** Header file for
** libarcade's color
** struct
*/

#pragma once

#include <algorithm>
#include <cstdint>
#include <array>


namespace Arcade {
    /**
     * Note:
     * The alpha channel (`alpha` field)
     * doesn't need to be supported by
     * the graphics library.
     *
     * It is nonetheless provided, as the
     * structure will contain 4 8-bit fields
     * due to padding anyway, so might as well
     * use it if possible.
     */
    struct Color {
        std::uint8_t red;
        std::uint8_t green;
        std::uint8_t blue;
        std::uint8_t alpha;

        constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 0xff) noexcept
            : red(r)
            , green(g)
            , blue(b)
            , alpha(a)
        {}

        constexpr Color(std::uint32_t color) noexcept
            : red   (color > 0xffffff ? (color & 0xff000000) >> 24 : (color & 0xff0000) >> 16)
            , green (color > 0xffffff ? (color & 0x00ff0000) >> 16 : (color & 0x00ff00) >> 8)
            , blue  (color > 0xffffff ? (color & 0x0000ff00) >>  8 : (color & 0x0000ff) >> 0)
            , alpha (color > 0xffffff ? (color & 0x000000ff) >>  0 : 0xff)
        {}

        constexpr Color() noexcept : Color( 0, 0, 0 ) {};

        constexpr std::uint32_t toRGB() const noexcept { return std::bit_cast<std::uint32_t>(*this); }

        constexpr Color operator+(const Color& other) const { return Color(*this) += other; }
        constexpr Color& operator+=(const Color& other)
        {
            red   = std::min(red + other.red, UINT8_MAX);
            green = std::min(green + other.green, UINT8_MAX);
            blue  = std::min(blue + other.blue, UINT8_MAX);
            alpha = std::min(alpha + other.alpha, UINT8_MAX);

            return *this;
        }

        constexpr Color operator-(const Color& other) const { return Color(*this) -= other; }
        constexpr Color& operator-=(const Color& other)
        {
            red   = std::max(red - other.red, 0);
            green = std::max(green - other.green, 0);
            blue  = std::max(blue - other.blue, 0);
            alpha = std::max(alpha - other.alpha, 0);

            return *this;
        }

        constexpr bool operator==(const Color& other) const { return !(*this != other); }
        constexpr bool operator!=(const Color& other) const
        {
            return
                (red != other.red)     ||
                (green != other.green) ||
                (blue != other.blue)   ||
                (alpha != other.alpha);
        }

        // make Colors struct implicitely convertible
        // to int to allow using it in switch/case stmts
        constexpr operator int() const noexcept { return toRGB(); }

        /**
         * Computes the squared distance
         * to another color. The alpha
         * channel is not taken into account.
         */
        constexpr unsigned int distanceSqr(const Color& other) const noexcept
        {
            return
                (red - other.red) * (red - other.red) +
                (green - other.green) * (green - other.green) +
                (blue - other.blue) * (blue - other.blue);
        }

        /**
         * Returns the closest simple color
         * matching this color.
         *
         * Simple colors are constexpr colors
         * defined in the Colors namespace below.
         */
        constexpr Color simple() const;
    };

    /**
     * Namespace containing all
     * of Arcade's "simple" colors.
     */
    inline namespace Colors {
        inline constexpr Color BLACK  = 0x000000;

        inline constexpr Color RED    = 0xff0000;
        inline constexpr Color GREEN  = 0x00ff00;
        inline constexpr Color BLUE   = 0x0000ff;

        inline constexpr Color PURPLE = 0xff00ff;
        inline constexpr Color YELLOW = 0xffff00;
        inline constexpr Color CYAN   = 0x00ffff;

        inline constexpr Color WHITE  = 0xffffff;
    }

    constexpr Color Color::simple() const
    {
        constexpr auto simpleCols = std::array{
            BLACK, WHITE,
            RED, GREEN, BLUE,
            PURPLE, YELLOW, CYAN,
        };

        double minDist = 10000000.0;
        Color minCol = BLACK;

        for (auto& col : simpleCols) {
            double dist = distanceSqr(col);

            if (dist >= minDist)
                continue;

            minDist = dist;
            minCol = col;
        }

        return minCol;
    }
}
