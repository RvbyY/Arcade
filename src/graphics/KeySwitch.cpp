#include "../../include/graphics/Ncurses/Ncurses.hpp"
#include "../../include/graphics/SDL2/SDL2.hpp"
#include "../../include/graphics/SFML/SfmlGraphic.hpp"
#include <SDL2/SDL.h>
#include <SFML/Window/Keyboard.hpp>

std::optional<Arcade::Event> NcursesGraphic::KeySwitch(int ch)
{
    switch (ch) {
        case 'a':           return Arcade::Event::ARC_KEY_A;
        case 'b':           return Arcade::Event::ARC_KEY_B;
        case 'c':           return Arcade::Event::ARC_KEY_C;
        case 'd':           return Arcade::Event::ARC_KEY_D;
        case 'e':           return Arcade::Event::ARC_KEY_E;
        case 'f':           return Arcade::Event::ARC_KEY_F;
        case 'g':           return Arcade::Event::ARC_KEY_G;
        case 'h':           return Arcade::Event::ARC_KEY_H;
        case 'i':           return Arcade::Event::ARC_KEY_I;
        case 'j':           return Arcade::Event::ARC_KEY_J;
        case 'k':           return Arcade::Event::ARC_KEY_K;
        case 'l':           return Arcade::Event::ARC_KEY_L;
        case 'm':           return Arcade::Event::ARC_KEY_M;
        case 'n':           return Arcade::Event::ARC_KEY_N;
        case 'o':           return Arcade::Event::ARC_KEY_O;
        case 'p':           return Arcade::Event::ARC_KEY_P;
        case 'q':           return Arcade::Event::ARC_KEY_Q;
        case 'r':           return Arcade::Event::ARC_KEY_R;
        case 's':           return Arcade::Event::ARC_KEY_S;
        case 't':           return Arcade::Event::ARC_KEY_T;
        case 'u':           return Arcade::Event::ARC_KEY_U;
        case 'v':           return Arcade::Event::ARC_KEY_V;
        case 'w':           return Arcade::Event::ARC_KEY_W;
        case 'x':           return Arcade::Event::ARC_KEY_X;
        case 'y':           return Arcade::Event::ARC_KEY_Y;
        case 'z':           return Arcade::Event::ARC_KEY_Z;
        case '1':           return Arcade::Event::ARC_KEY_1;
        case '2':           return Arcade::Event::ARC_KEY_2;
        case '3':           return Arcade::Event::ARC_KEY_3;
        case '4':           return Arcade::Event::ARC_KEY_4;
        case '5':           return Arcade::Event::ARC_KEY_5;
        case '6':           return Arcade::Event::ARC_KEY_6;
        case '7':           return Arcade::Event::ARC_KEY_7;
        case '8':           return Arcade::Event::ARC_KEY_8;
        case '9':           return Arcade::Event::ARC_KEY_9;
        case '0':           return Arcade::Event::ARC_KEY_0;

        case KEY_F(1):      return Arcade::Event::ARC_KEY_F1;
        case KEY_F(2):      return Arcade::Event::ARC_KEY_F2;
        case KEY_F(3):      return Arcade::Event::ARC_KEY_F3;
        case KEY_F(4):      return Arcade::Event::ARC_KEY_F4;
        case KEY_F(5):      return Arcade::Event::ARC_KEY_F5;
        case KEY_F(6):      return Arcade::Event::ARC_KEY_F6;
        case KEY_F(7):      return Arcade::Event::ARC_KEY_F7;
        case KEY_F(8):      return Arcade::Event::ARC_KEY_F8;
        case KEY_F(9):      return Arcade::Event::ARC_KEY_F9;
        case KEY_F(10):     return Arcade::Event::ARC_KEY_F10;
        case KEY_F(11):     return Arcade::Event::ARC_KEY_F11;
        case KEY_F(12):     return Arcade::Event::ARC_KEY_F12;

        case KEY_UP:        return Arcade::Event::ARC_ARROW_UP;
        case KEY_DOWN:      return Arcade::Event::ARC_ARROW_DOWN;
        case KEY_LEFT:      return Arcade::Event::ARC_ARROW_LEFT;
        case KEY_RIGHT:     return Arcade::Event::ARC_ARROW_RIGHT;

        case KEY_BACKSPACE:
        case 127:           return Arcade::Event::ARC_KEY_BACKSPACE;

        case KEY_ENTER:
        case '\n':
        case '\r':          return Arcade::Event::ARC_KEY_RETURN;

        case ' ':           return Arcade::Event::ARC_KEY_SPACE;
        case '\t':          return Arcade::Event::ARC_KEY_TAB;
        case 27:            return Arcade::Event::ARC_KEY_ESC;
        case KEY_RESIZE:    return Arcade::Event::ARC_RESIZE;

        default:            return {};
    }
}

std::optional<Arcade::Event> SDL2Graphic::KeySwitch(int key)
{
    switch (key) {
        case SDLK_a: return Arcade::Event::ARC_KEY_A;
        case SDLK_b: return Arcade::Event::ARC_KEY_B;
        case SDLK_c: return Arcade::Event::ARC_KEY_C;
        case SDLK_d: return Arcade::Event::ARC_KEY_D;
        case SDLK_e: return Arcade::Event::ARC_KEY_E;
        case SDLK_f: return Arcade::Event::ARC_KEY_F;
        case SDLK_g: return Arcade::Event::ARC_KEY_G;
        case SDLK_h: return Arcade::Event::ARC_KEY_H;
        case SDLK_i: return Arcade::Event::ARC_KEY_I;
        case SDLK_j: return Arcade::Event::ARC_KEY_J;
        case SDLK_k: return Arcade::Event::ARC_KEY_K;
        case SDLK_l: return Arcade::Event::ARC_KEY_L;
        case SDLK_m: return Arcade::Event::ARC_KEY_M;
        case SDLK_n: return Arcade::Event::ARC_KEY_N;
        case SDLK_o: return Arcade::Event::ARC_KEY_O;
        case SDLK_p: return Arcade::Event::ARC_KEY_P;
        case SDLK_q: return Arcade::Event::ARC_KEY_Q;
        case SDLK_r: return Arcade::Event::ARC_KEY_R;
        case SDLK_s: return Arcade::Event::ARC_KEY_S;
        case SDLK_t: return Arcade::Event::ARC_KEY_T;
        case SDLK_u: return Arcade::Event::ARC_KEY_U;
        case SDLK_v: return Arcade::Event::ARC_KEY_V;
        case SDLK_w: return Arcade::Event::ARC_KEY_W;
        case SDLK_x: return Arcade::Event::ARC_KEY_X;
        case SDLK_y: return Arcade::Event::ARC_KEY_Y;
        case SDLK_z: return Arcade::Event::ARC_KEY_Z;

        case SDLK_1: return Arcade::Event::ARC_KEY_1;
        case SDLK_2: return Arcade::Event::ARC_KEY_2;
        case SDLK_3: return Arcade::Event::ARC_KEY_3;
        case SDLK_4: return Arcade::Event::ARC_KEY_4;
        case SDLK_5: return Arcade::Event::ARC_KEY_5;
        case SDLK_6: return Arcade::Event::ARC_KEY_6;
        case SDLK_7: return Arcade::Event::ARC_KEY_7;
        case SDLK_8: return Arcade::Event::ARC_KEY_8;
        case SDLK_9: return Arcade::Event::ARC_KEY_9;
        case SDLK_0: return Arcade::Event::ARC_KEY_0;

        case SDLK_F1:  return Arcade::Event::ARC_KEY_F1;
        case SDLK_F2:  return Arcade::Event::ARC_KEY_F2;
        case SDLK_F3:  return Arcade::Event::ARC_KEY_F3;
        case SDLK_F4:  return Arcade::Event::ARC_KEY_F4;
        case SDLK_F5:  return Arcade::Event::ARC_KEY_F5;
        case SDLK_F6:  return Arcade::Event::ARC_KEY_F6;
        case SDLK_F7:  return Arcade::Event::ARC_KEY_F7;
        case SDLK_F8:  return Arcade::Event::ARC_KEY_F8;
        case SDLK_F9:  return Arcade::Event::ARC_KEY_F9;
        case SDLK_F10: return Arcade::Event::ARC_KEY_F10;
        case SDLK_F11: return Arcade::Event::ARC_KEY_F11;
        case SDLK_F12: return Arcade::Event::ARC_KEY_F12;

        case SDLK_UP:    return Arcade::Event::ARC_ARROW_UP;
        case SDLK_DOWN:  return Arcade::Event::ARC_ARROW_DOWN;
        case SDLK_LEFT:  return Arcade::Event::ARC_ARROW_LEFT;
        case SDLK_RIGHT: return Arcade::Event::ARC_ARROW_RIGHT;

        case SDLK_BACKSPACE: return Arcade::Event::ARC_KEY_BACKSPACE;
        case SDLK_RETURN:
        case SDLK_KP_ENTER:  return Arcade::Event::ARC_KEY_RETURN;
        case SDLK_SPACE:     return Arcade::Event::ARC_KEY_SPACE;
        case SDLK_TAB:       return Arcade::Event::ARC_KEY_TAB;
        case SDLK_ESCAPE:    return Arcade::Event::ARC_KEY_ESC;

        default: return {};
    }
}

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
