#include <dlfcn.h>
#include <iostream>
#include "../lib/libarcade/Arcade/display.hpp"
#include "Arcade/utils/text.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_graphic_lib>" << std::endl;
        return 1;
    }

    Arcade::Color color(255, 0, 0);

    void* handle = dlopen(argv[1], RTLD_NOW);
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
        dlclose(handle);
        return 1;
    }

    Arcade::IDisplay* graphic = create();
    graphic->open();
    graphic->draw(Arcade::Text{"lol"});
    graphic->display();

    char c;
    std::cin >> c;
    graphic->close();
    destroy(graphic);
    dlclose(handle);
    return 0;
}
