/*
** EPITECH PROJECT, 2026
** Project - Arcade
** File description:
** Header file for
** libarcade's text
** struct
*/

#pragma once

#include "colors.hpp"
#include "types.hpp"
#include <string_view>
#include <string>


namespace Arcade {
    /**
     * Note:
     * Since the text's content
     * is likely to contain variable
     * elements, we take ownership of
     * the content (hence std::string
     * instead of std::string_view)
     * in order to make dealing with
     * text easier to the user of the
     * library.
     */
    struct Text {
        Coordinate x;
        Coordinate y;
        std::string content;
        Color color;

        explicit Text(std::string_view content)
            : Text(content, 0, 0)
        {}

        Text(std::string_view content, Coordinate x, Coordinate y, Color col = 0xffffffff)
            : x(x), y(y)
            , content(content)
            , color(col)
        {}
    };
}
