#include <dlfcn.h>
#include <iostream>
#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"

int EntryArgsCheck(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_graphic_lib>" << std::endl;
        return 1;
    }
    return 0;
}

void *HandleDlOpen(char **argv, void *handle)
{
    handle = dlopen(argv[1], RTLD_NOW);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return nullptr;
    }
    return handle;
}

int ProgrammEntrypoint(int argc, char **argv)
{
    EntryArgsCheck(argc, argv);
    Arcade::Color color(255, 0, 0);

    void *handle = HandleDlOpen(argv, handle);

    auto createDisplay = reinterpret_cast<Arcade::DisplayEntryPointFnc>(::dlsym(handle, Arcade::DISPLAY_ENTRYPOINT));

    if (!createDisplay) {
        std::cerr << "Not a game library.\n";
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
    return 0;
}
