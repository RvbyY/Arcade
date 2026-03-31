#include <dlfcn.h>
#include <iostream>
#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_graphic_lib>" << std::endl;
        return 1;
    }

    void* handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return 1;
    }

    auto createDisplay = reinterpret_cast<Arcade::DisplayEntryPointFnc>(handle, Arcade::DISPLAY_ENTRYPOINT);
    // destroy_t destroy = (destroy_t)dlsym(handle, "destroy");

    if (!createDisplay) {
        std::cerr << "Not a game library.\n";
        // std::cerr << "Symbol error\n";
        dlclose(handle);
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


    // create_t create = (create_t)dlsym(handle, "create");
    // destroy_t destroy = (destroy_t)dlsym(handle, "destroy");

    // if (!create || !destroy) {
    //     std::cerr << "Symbol error\n";
    //     dlclose(handle);
    //     return 1;
    // }

    // Arcade::IDisplay* graphic = create();
    // graphic->open();
    // graphic->draw(Arcade::Text{"lol"});
    // graphic->display();

    // char c;
    // std::cin >> c;
    // graphic->close();
    // // destroy(graphic);
    // dlclose(handle);
    return 0;
}
