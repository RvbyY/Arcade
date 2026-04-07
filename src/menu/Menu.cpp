#include "../../include/menu/menu.hpp"

void MenuLoop(std::size_t selectedButton, Arcade::IDisplay* graphic, void *handle)
{
    const Arcade::Color selectedColor(255, 255, 0);
    const Arcade::Color normalColor(255, 255, 255);

    UsernameScreen(graphic);

    while (graphic->isOpen()) {
        graphic->clear();

        graphic->draw(Arcade::Text{"[ Snake ]", 10, 5, selectedButton == 1 ? selectedColor : normalColor});
        graphic->draw(Arcade::Text{"[ Autre Jeu ]", 10, 7, selectedButton == 0 ? selectedColor : normalColor});
        graphic->draw(Arcade::Text{"[ Encore Autre Jeu ]", 10, 9, selectedButton == 0 ? selectedColor : normalColor});
        graphic->draw(Arcade::Text{"[ Exit ]", 50, 20, selectedButton == 0 ? selectedColor : normalColor});
        graphic->draw(Arcade::Text{"[ Leaderboard ]", 100, 5, selectedButton == 0 ? selectedColor : normalColor});
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
                }
                break;

            case Arcade::Event::ARC_KEY_ESC:
            case Arcade::Event::ARC_CLOSE:
                graphic->close();
                break;

            default:
                break;
        }
    }
}