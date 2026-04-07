/*
** EPITECH PROJECT, 2026
** Project - Arcade
** File description:
** Header file for
** libarcade's constants
*/

#pragma once


namespace Arcade {
    inline namespace Constants {
        /**
         * Entrypoint symbol names.
         *
         * Game libraries must name
         * their entrypoint after the
         * GAME_ENTRYPOINT constant,
         * and display libraries must
         * name their entrypoint after
         * DISPLAY_ENTRYPOINT.
         *
         * These constants are a convenience
         * provided for use with dlsym() (from dlfcn.h).
         *
         * The reason these are const char arrays
         * instead of `std::string_view`s is to allow
         * them to be used in template arguments
         * (since addresses are not known at compile-time,
         * arrays have to be used instead).
         */
        inline constexpr const char GAME_ENTRYPOINT[] = "get_game";
        inline constexpr const char DISPLAY_ENTRYPOINT[] = "get_display";
    }
}
