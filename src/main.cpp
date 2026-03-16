#include <dlfcn.h>
#include <iostream>
#include "graphics/IGraphic.hpp"

int main()
{
    void* handle = dlopen("./lib/arcade_ncurses.so", RTLD_NOW);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return 1;
    }

    using create_t = IGraphic* (*)();
    using destroy_t = void (*)(IGraphic*);

    create_t create = (create_t)dlsym(handle, "create");
    destroy_t destroy = (destroy_t)dlsym(handle, "destroy");

    if (!create || !destroy) {
        std::cerr << "Symbol error\n";
        return 1;
    }

    IGraphic* graphic = create();

    graphic->init();
    graphic->draw();
    graphic->stop();

    destroy(graphic);
    dlclose(handle);

    return 0;
}