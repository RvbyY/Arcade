#include "../../include/graphics/Ncurses/Ncurses.hpp"
#include "../../include/graphics/SDL2/SDL2.hpp"
#include <SDL2/SDL.h>

std::optional<Arcade::Event> NcursesGraphic::KeySwitch(int ch)
{
    if (ch >= 'A' && ch <= 'Z')
        ch += ('a' - 'A');

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
