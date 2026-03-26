#include <dlfcn.h>
#include <iostream>
#include "Arcade/game.hpp"
#include "Arcade/display.hpp"

int main()
{
        Arcade::Color color(255, 0, 0);
    std::cout << "Color: " << (int)color.red << ", " << (int)color.green << ", " << (int)color.blue << std::endl;

    void* handle = dlopen("./lib/arcade_ncurses.so", RTLD_NOW);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return 1;
    }

    using create_t = Arcade::IDisplay* (*)();
    using destroy_t = void (*)(Arcade::IDisplay*);

    create_t create = (create_t)dlsym(handle, "create");
    destroy_t destroy = (destroy_t)dlsym(handle, "destroy");

    if (!create || !destroy) {
        std::cerr << "Symbol error\n";
        return 1;
    }

    Arcade::IDisplay* graphic = create();

    graphic->open();
    graphic->display();
    graphic->close();

    destroy(graphic);
    dlclose(handle);

    return 0;
}