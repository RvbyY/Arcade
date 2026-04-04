/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Sat, Mar, 2026                                                     *
 * Title           - G-OOP-400-STG-4-1-arcade-5                                         *
 * Description     -                                                                    *
 *     grid                                                                             *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *         ░        ░       ░░        ░        ░        ░░      ░░  ░░░░  ░             *
 *         ▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒▒▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒             *
 *         ▓      ▓▓▓       ▓▓▓▓▓  ▓▓▓▓▓▓▓  ▓▓▓▓      ▓▓▓  ▓▓▓▓▓▓▓        ▓             *
 *         █  ███████  ██████████  ███████  ████  ███████  ████  █  ████  █             *
 *         █        █  ███████        ████  ████        ██      ██  ████  █             *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#pragma once

#include <vector>
#include <concepts>
#include "Arcade/utils.hpp"

namespace Tools
{
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    enum CellType {
        WALL,
        EMPTY,
        APPLE,
        BODY,
        HEAD,
        PACGUN,
        GHOST
    };

    struct Vec2 {
        Arcade::Coordinate x;
        Arcade::Coordinate y;

        Vec2 operator+(const Vec2& other) const
        {
            return {
                x + other.x, y + other.y
            };
        }

        Vec2 operator-(const Vec2& other) const
        {
            return {
                x - other.x, y - other.y
            };
        }

        bool operator==(const Vec2& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vec2& other) const
        {
            return !(*this == other);
        }
    };

    struct Vec2Hash {
        std::size_t operator()(const Vec2& v) const {
            return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 16);
        }
    };

    template<typename T>
    struct Grid {
            int width;
            int height;
            std::vector<T> cells;

            Grid(int w, int h, T defaultValue = T{}) : width(w), height(h), cells(w * h, defaultValue) {}
            ~Grid() = default;

            void reset(T value)
            {
                cells = std::vector<T>(width * height, value);
            }

            int index(Vec2 pos) const
            {
                return pos.y * width + pos.x;
            }

            bool inBounds(Vec2 pos) const
            {
                return pos.x >= 0 && pos.x < width
                    && pos.y >= 0 && pos.y < height;
            }

            T getPosition(Vec2 pos) const
            {
                return cells[index(pos)];
            }

            void setPosition(Vec2 pos, T value)
            {
                cells[index(pos)] = value;
            }

            Vec2 wrap(Vec2 pos) const
            {
                return {
                    ((pos.x % width) + width) % width,
                    ((pos.y % height) + height) % height
                };
            }
    };
}
