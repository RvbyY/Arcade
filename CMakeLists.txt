cmake_minimum_required(VERSION 3.16)

project(arcade)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(arcade
    src/main.cpp
    src/graphics/ncurses/Ncurses.cpp
)

add_library(arcadeNcurses SHARED
    graphics/ncurses/Ncurses.cpp
)

add_library(arcadeSdl2 SHARED
    graphics/sdl2/SDL2.cpp
)

# add_library(arcade_game SHARED
#     games/Gamedir/GameName.cpp
# )

target_include_directories(MyLibrary PUBLIC include)

add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE MyLibrary)

target_include_directories(arcade_interfaces INTERFACE
    ${CMAKE_SOURCE_DIR}/include
)