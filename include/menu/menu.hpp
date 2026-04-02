#include <cstddef>
#include <dlfcn.h>
#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"

void MenuLoop(std::size_t selectedButton, Arcade::IDisplay* graphic, void *handle);
int ProgrammEntrypoint(int, char**);
std::string UsernameScreen(Arcade::IDisplay* graphic);