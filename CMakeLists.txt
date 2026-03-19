##
## EPITECH PROJECT, 2026
## Project - ARCADE
## File description:
## Main CMake file
##

cmake_minimum_required(VERSION 3.15)
project(Arcade VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# ─── Output directories ───────────────────────────────────────────────────────
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})        # arcade binary → root
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)    # .so files   → lib/

# ─── Main executable ─────────────────────────────────────────────────────────
add_executable(arcade
    src/main.cpp
)
target_include_directories(arcade PUBLIC "include")

# ─── Helper macro to declare a shared library ────────────────────────────────
# Usage: add_arcade_lib(<target_name> <sources...>)
macro(add_arcade_lib NAME)
    add_library(${NAME} SHARED ${ARGN})
    target_include_directories(${NAME} PUBLIC "include")
    set_target_properties(${NAME} PROPERTIES
        PREFIX ""          # avoid "lib" prefix → arcade_ncurses.so not libarcade_ncurses.so
        SUFFIX ".so"       # force .so even on macOS
    )
endmacro()

# ─── Graphics libraries ───────────────────────────────────────────────────────
add_arcade_lib(arcade_ncurses
    src/graphics/ncurses/Ncurses.cpp
)

add_arcade_lib(arcade_sdl2
    src/graphics/SDL2/SDL2.cpp
)

# ─── Game libraries ───────────────────────────────────────────────────────────