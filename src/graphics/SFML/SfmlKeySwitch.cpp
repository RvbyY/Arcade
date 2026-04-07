#include "../../../include/graphics/SFML/SfmlGraphic.hpp"

std::optional<Arcade::Event> SfmlGraphic::KeySwitch(int key)
{
    switch (key) {
        case sf::Keyboard::A: return Arcade::Event::ARC_KEY_A;
        case sf::Keyboard::B: return Arcade::Event::ARC_KEY_B;
        case sf::Keyboard::C: return Arcade::Event::ARC_KEY_C;
        case sf::Keyboard::D: return Arcade::Event::ARC_KEY_D;
        case sf::Keyboard::E: return Arcade::Event::ARC_KEY_E;
        case sf::Keyboard::F: return Arcade::Event::ARC_KEY_F;
        case sf::Keyboard::G: return Arcade::Event::ARC_KEY_G;
        case sf::Keyboard::H: return Arcade::Event::ARC_KEY_H;
        case sf::Keyboard::I: return Arcade::Event::ARC_KEY_I;
        case sf::Keyboard::J: return Arcade::Event::ARC_KEY_J;
        case sf::Keyboard::K: return Arcade::Event::ARC_KEY_K;
        case sf::Keyboard::L: return Arcade::Event::ARC_KEY_L;
        case sf::Keyboard::M: return Arcade::Event::ARC_KEY_M;
        case sf::Keyboard::N: return Arcade::Event::ARC_KEY_N;
        case sf::Keyboard::O: return Arcade::Event::ARC_KEY_O;
        case sf::Keyboard::P: return Arcade::Event::ARC_KEY_P;
        case sf::Keyboard::Q: return Arcade::Event::ARC_KEY_Q;
        case sf::Keyboard::R: return Arcade::Event::ARC_KEY_R;
        case sf::Keyboard::S: return Arcade::Event::ARC_KEY_S;
        case sf::Keyboard::T: return Arcade::Event::ARC_KEY_T;
        case sf::Keyboard::U: return Arcade::Event::ARC_KEY_U;
        case sf::Keyboard::V: return Arcade::Event::ARC_KEY_V;
        case sf::Keyboard::W: return Arcade::Event::ARC_KEY_W;
        case sf::Keyboard::X: return Arcade::Event::ARC_KEY_X;
        case sf::Keyboard::Y: return Arcade::Event::ARC_KEY_Y;
        case sf::Keyboard::Z: return Arcade::Event::ARC_KEY_Z;

        case sf::Keyboard::Num1: return Arcade::Event::ARC_KEY_1;
        case sf::Keyboard::Num2: return Arcade::Event::ARC_KEY_2;
        case sf::Keyboard::Num3: return Arcade::Event::ARC_KEY_3;
        case sf::Keyboard::Num4: return Arcade::Event::ARC_KEY_4;
        case sf::Keyboard::Num5: return Arcade::Event::ARC_KEY_5;
        case sf::Keyboard::Num6: return Arcade::Event::ARC_KEY_6;
        case sf::Keyboard::Num7: return Arcade::Event::ARC_KEY_7;
        case sf::Keyboard::Num8: return Arcade::Event::ARC_KEY_8;
        case sf::Keyboard::Num9: return Arcade::Event::ARC_KEY_9;
        case sf::Keyboard::Num0: return Arcade::Event::ARC_KEY_0;

        case sf::Keyboard::F1:  return Arcade::Event::ARC_KEY_F1;
        case sf::Keyboard::F2:  return Arcade::Event::ARC_KEY_F2;
        case sf::Keyboard::F3:  return Arcade::Event::ARC_KEY_F3;
        case sf::Keyboard::F4:  return Arcade::Event::ARC_KEY_F4;
        case sf::Keyboard::F5:  return Arcade::Event::ARC_KEY_F5;
        case sf::Keyboard::F6:  return Arcade::Event::ARC_KEY_F6;
        case sf::Keyboard::F7:  return Arcade::Event::ARC_KEY_F7;
        case sf::Keyboard::F8:  return Arcade::Event::ARC_KEY_F8;
        case sf::Keyboard::F9:  return Arcade::Event::ARC_KEY_F9;
        case sf::Keyboard::F10: return Arcade::Event::ARC_KEY_F10;
        case sf::Keyboard::F11: return Arcade::Event::ARC_KEY_F11;
        case sf::Keyboard::F12: return Arcade::Event::ARC_KEY_F12;

        case sf::Keyboard::Up:    return Arcade::Event::ARC_ARROW_UP;
        case sf::Keyboard::Down:  return Arcade::Event::ARC_ARROW_DOWN;
        case sf::Keyboard::Left:  return Arcade::Event::ARC_ARROW_LEFT;
        case sf::Keyboard::Right: return Arcade::Event::ARC_ARROW_RIGHT;

        case sf::Keyboard::BackSpace:  return Arcade::Event::ARC_KEY_BACKSPACE;
        case sf::Keyboard::Enter:      return Arcade::Event::ARC_KEY_RETURN;
        case sf::Keyboard::Space:      return Arcade::Event::ARC_KEY_SPACE;
        case sf::Keyboard::Tab:        return Arcade::Event::ARC_KEY_TAB;
        case sf::Keyboard::Escape:     return Arcade::Event::ARC_KEY_ESC;

        default: return {};
    }
}
