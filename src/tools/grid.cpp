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

#include "grid.hpp"

template <typename T>
int tools::grid<T>::index(Vec2 pos) const
{
    return pos.y * _width + pos.x;
}

template <typename T>
bool tools::grid<T>::inBounds(Vec2 pos) const
{
    return pos.x >= 0 && pos.x < _width
        && pos.y >= 0 && pos.y < _height;
}

template <typename T>
T tools::grid<T>::getPosition(Vec2 pos) const
{
    return _cells[tools::grid<T>::index(pos)];
}

template <typename T>
void tools::grid<T>::setPosition(Vec2 pos, T value)
{
    _cells[tools::grid<T>::index(pos)];
}

template <typename T>
tools::Vec2 tools::grid<T>::wrap(Vec2 pos) const
{
    return {
        ((pos.x % _width) + _width) % _width,
        ((pos.y % _height) + _height) % _height
    };
}