#include "../../include/menu/menu.hpp"
#include <iostream>

int EntryArgsCheck(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_graphic_lib>" << std::endl;
        return 1;
    }
    return 0;
}

void *HandleDlOpen(char **argv)
{
    void* handle = dlopen(argv[1], RTLD_NOW);
    if (!handle) {
        std::cerr << dlerror() << std::endl;
        return nullptr;
    }
    return handle;
}

int ProgrammEntrypoint(int argc, char **argv)
{
    const int status = EntryArgsCheck(argc, argv);
    if (status != 0) {
        return status;
    }

    void *handle = HandleDlOpen(argv);
    if (!handle) {
        return 1;
    }

    auto createDisplay = reinterpret_cast<Arcade::DisplayEntryPointFnc>(::dlsym(handle, Arcade::DISPLAY_ENTRYPOINT));
    if (!createDisplay) {
        std::cerr << "Not a display library.\n";
        dlclose(handle);
        return 1;
    }

    Arcade::IDisplay* graphic = createDisplay();
    if (!graphic) {
        std::cerr << "Failed to instantiate display.\n";
        dlclose(handle);
        return 1;
    }

    graphic->open();

    std::size_t selectedButton = 0;

    MenuLoop(selectedButton, graphic, handle);

    graphic->close();
    delete graphic;
    dlclose(handle);
    return 0;
}

