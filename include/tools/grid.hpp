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

#ifndef INCLUDED_GRID_HPP
    #define INCLUDED_GRID_HPP

#include <vector>

namespace tools
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
        PACGUN,
        GHOST
    };

    struct Vec2 {
        int x;
        int y;

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
    class grid {
        private:
        public:
            int _width;
            int _height;
            std::vector<T> _cells;
            grid(int w, int h, T defaultValue = T{}) : _width(w), _height(h), _cells(w * h, defaultValue) {}
            int index(Vec2 pos) const;
            bool inBounds(Vec2 pos) const;
            T getPosition(Vec2 pos) const;
            void setPosition(Vec2 pos, T value);
            Vec2 wrap(Vec2 pos) const;
            ~grid() = default;
    };
}

#endif
