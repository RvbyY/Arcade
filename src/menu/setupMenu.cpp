#include "../../include/menu/menu.hpp"
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
    const Arcade::Color selectedColor(255, 255, 0);
    const Arcade::Color normalColor(255, 255, 255);

    while (graphic->isOpen()) {
        graphic->clear();

        graphic->draw(Arcade::Text{"[ Play ]", 10, 5, selectedButton == 0 ? selectedColor : normalColor});
        graphic->draw(Arcade::Text{"[ Exit ]", 10, 7, selectedButton == 1 ? selectedColor : normalColor});
        graphic->draw(Arcade::Text{">", 8, selectedButton == 0 ? 5 : 7, selectedColor});

        graphic->display();

        const auto event = graphic->pollEvent();
        if (!event.has_value()) {
            continue;
        }

        switch (*event) {
            case Arcade::Event::ARC_ARROW_UP:
            case Arcade::Event::ARC_ARROW_LEFT:
                selectedButton = selectedButton == 0 ? 1 : 0;
                break;

            case Arcade::Event::ARC_ARROW_DOWN:
            case Arcade::Event::ARC_ARROW_RIGHT:
                selectedButton = selectedButton == 0 ? 1 : 0;
                break;

            case Arcade::Event::ARC_KEY_RETURN:
            case Arcade::Event::ARC_KEY_SPACE:
                if (selectedButton == 1) {
                    graphic->close();
                    delete graphic;
                    dlclose(handle);
                    return 0;
                }
                break;

            case Arcade::Event::ARC_KEY_ESC:
            case Arcade::Event::ARC_CLOSE:
                graphic->close();
                delete graphic;
                dlclose(handle);
                return 0;

            default:
                break;
        }
    }

    graphic->close();
    delete graphic;
    dlclose(handle);
    return 0;
}

int main(int argc, char** argv)
{
    if (ProgrammEntrypoint(argc, argv) == 1) {
        return 1;
    }
    else return 0;
}

