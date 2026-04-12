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
    src/core/core.cpp
    src/core/game_loop.cpp
    src/core/load_libraries.cpp
    src/menu/SelectMenu.cpp
    src/menu/UserInputMenu.cpp
    src/menu/UsernameSelection.cpp
    src/core/overlays/debugOverlay.cpp
    src/core/overlays/leaderboardOverlay.cpp
    src/core/playerContainer/playerContainer.cpp
)
target_include_directories(arcade PRIVATE include lib/libarcade)

# ─── Helper macro to declare a shared library ────────────────────────────────
# Usage: add_arcade_lib(<target_name> <sources...>)
macro(add_arcade_lib NAME)
    add_library(${NAME} SHARED ${ARGN})
    set_target_properties(${NAME} PROPERTIES
        PREFIX ""          # avoid "lib" prefix → arcade_ncurses.so not libarcade_ncurses.so
        SUFFIX ".so"       # force .so even on macOS
    )
endmacro()

# ─── Arcade lib ───────────────────────────────────────────────────────────────

set(LIBARCADE_SRC_DIR ${CMAKE_SOURCE_DIR}/lib/libarcade)
set(LIBARCADE_MAKEFILE ${LIBARCADE_SRC_DIR}/Makefile)
option(ARCADE_FORCE_LIBARCADE_CLONE "Force re-cloning lib/libarcade from the remote repository" OFF)

if (ARCADE_FORCE_LIBARCADE_CLONE)
    include(ExternalProject)
    ExternalProject_Add(libarcade
        GIT_REPOSITORY git@github.com:Bard-Gaming/libarcade.git
        GIT_TAG main
        SOURCE_DIR ${LIBARCADE_SRC_DIR}
        UPDATE_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} no-repo
        INSTALL_COMMAND ""
        BUILD_IN_SOURCE 1
    )
elseif (EXISTS "${LIBARCADE_SRC_DIR}")
    if (EXISTS "${LIBARCADE_MAKEFILE}")
        add_custom_target(libarcade
            COMMAND ${CMAKE_MAKE_PROGRAM} no-repo
            WORKING_DIRECTORY ${LIBARCADE_SRC_DIR}
            COMMENT "Cleaning existing lib/libarcade checkout"
        )
    else()
        add_custom_target(libarcade
            COMMAND ${CMAKE_COMMAND} -E echo "Using existing lib/libarcade directory"
        )
    endif()
else()
    message(FATAL_ERROR
        "Missing ${LIBARCADE_SRC_DIR}. Provide the directory locally or configure with "
        "-DARCADE_FORCE_LIBARCADE_CLONE=ON to clone it."
    )
endif()

add_dependencies(arcade libarcade)

target_include_directories(arcade PUBLIC lib/libarcade)
target_link_libraries(arcade PUBLIC ncurses)

# ─── Graphics libraries ───────────────────────────────────────────────────────
add_arcade_lib(arcade_ncurses
    src/graphics/ncurses/Ncurses.cpp
    src/graphics/ncurses/NcursesKeySwitch.cpp
)
target_link_libraries(arcade_ncurses PRIVATE -lncurses)

add_arcade_lib(arcade_sdl2
    src/graphics/SDL2/SDL2.cpp
    src/graphics/SDL2/SDL2KeySwitch.cpp
)
target_link_libraries(arcade_sdl2 PRIVATE SDL2 SDL2_ttf)

add_arcade_lib(arcade_sfml
    src/graphics/SFML/SfmlGraphic.cpp
    src/graphics/SFML/SfmlKeySwitch.cpp
)
target_link_libraries(arcade_sfml PRIVATE sfml-graphics sfml-window sfml-system)


# ─── Game libraries ───────────────────────────────────────────────────────────
add_arcade_lib(arcade_snake
    src/game/snake/Snake.cpp
)
target_include_directories(arcade_snake PRIVATE include lib/libarcade)

add_arcade_lib(arcade_pacman
    src/game/pacman/pacman.cpp
)
target_include_directories(arcade_pacman PRIVATE include lib/libarcade)


# ─── Game libraries ───────────────────────────────────────────────────────────
