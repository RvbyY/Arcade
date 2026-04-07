#include "../../include/menu/menu.hpp"

char EventToChar(Arcade::Event event)
{
    switch (event) {
        case Arcade::Event::ARC_KEY_A: return 'a';
        case Arcade::Event::ARC_KEY_B: return 'b';
        case Arcade::Event::ARC_KEY_C: return 'c';
        case Arcade::Event::ARC_KEY_D: return 'd';
        case Arcade::Event::ARC_KEY_E: return 'e';
        case Arcade::Event::ARC_KEY_F: return 'f';
        case Arcade::Event::ARC_KEY_G: return 'g';
        case Arcade::Event::ARC_KEY_H: return 'h';
        case Arcade::Event::ARC_KEY_I: return 'i';
        case Arcade::Event::ARC_KEY_J: return 'j';
        case Arcade::Event::ARC_KEY_K: return 'k';
        case Arcade::Event::ARC_KEY_L: return 'l';
        case Arcade::Event::ARC_KEY_M: return 'm';
        case Arcade::Event::ARC_KEY_N: return 'n';
        case Arcade::Event::ARC_KEY_O: return 'o';
        case Arcade::Event::ARC_KEY_P: return 'p';
        case Arcade::Event::ARC_KEY_Q: return 'q';
        case Arcade::Event::ARC_KEY_R: return 'r';
        case Arcade::Event::ARC_KEY_S: return 's';
        case Arcade::Event::ARC_KEY_T: return 't';
        case Arcade::Event::ARC_KEY_U: return 'u';
        case Arcade::Event::ARC_KEY_V: return 'v';
        case Arcade::Event::ARC_KEY_W: return 'w';
        case Arcade::Event::ARC_KEY_X: return 'x';
        case Arcade::Event::ARC_KEY_Y: return 'y';
        case Arcade::Event::ARC_KEY_Z: return 'z';
        default:            return 0;
    }
}

std::string UsernameScreen(Arcade::IDisplay* graphic)
{
    const Arcade::Color white(255, 255, 255);
    const Arcade::Color yellow(255, 255, 0);
    std::string username;

    while (graphic->isOpen()) {
        graphic->clear();
        graphic->draw(Arcade::Text{"Enter your username:", 10, 5, white});
        graphic->draw(Arcade::Text{"> " + username + "_", 10, 7, yellow});
        graphic->draw(Arcade::Text{"Press ENTER to confirm", 10, 10, white});
        graphic->display();

        const auto event = graphic->pollEvent();
        if (!event.has_value())
            continue;

        switch (*event) {
            case Arcade::Event::ARC_KEY_RETURN:
                if (!username.empty())
                    return username;
                break;
            case Arcade::Event::ARC_KEY_BACKSPACE:
                if (!username.empty())
                    username.pop_back();
                break;
            case Arcade::Event::ARC_KEY_ESC:
            case Arcade::Event::ARC_CLOSE:
                graphic->close();
                return "";
            default:
                char c = EventToChar(*event);
                if (c != 0 && username.size() < 16)
                    username += c;
                break;
        }
    }
    return "";
}