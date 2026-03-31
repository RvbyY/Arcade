#include <dlfcn.h>
#include <iostream>
#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"

int main(int ac, char **av)
{
        Arcade::Color color(255, 0, 0);
    std::cout << "Color: " << (int)color.red << ", " << (int)color.green << ", " << (int)color.blue << std::endl;

    void* handle = dlopen(av[1], RTLD_NOW);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return 1;
    }

    auto createDisplay = reinterpret_cast<Arcade::DisplayEntryPointFnc>(handle, Arcade::DISPLAY_ENTRYPOINT);
    // destroy_t destroy = (destroy_t)dlsym(handle, "destroy");

    if (!createDisplay) {
        std::cerr << "Not a game library.\n";
        return 1;
    }

    Arcade::IDisplay* graphic = createDisplay();

    graphic->open();

    graphic->draw(Arcade::Text{"hihi"});
    graphic->display();

    char c;
    std::cin >> c;
    graphic->close();

    delete graphic;
    dlclose(handle);

    return 0;
}