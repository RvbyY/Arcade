#include <cstddef>
#include <dlfcn.h>
#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"

void MenuLoop(std::size_t selectedButton, Arcade::IDisplay* graphic, void *handle);
int ProgrammEntrypoint(int, char**);
std::string UsernameScreen(Arcade::IDisplay* graphic);

// faire une game qui prend un paramètre en + qui n'est
// pas un .so externe et qu'on peut utiliser dans le core
// dans le core créer le menu à part avec le core en option du constructeur
