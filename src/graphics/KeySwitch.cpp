#include "../../include/graphics/Ncurses/Ncurses.hpp"

std::optional<Arcade::Event> NcursesGraphic::KeySwitch(int ch)
{
    switch (ch) {
        case 'a': case 'A': return Arcade::Event::ARC_KEY_A;
        case 'b': case 'B': return Arcade::Event::ARC_KEY_B;
        case 'c': case 'C': return Arcade::Event::ARC_KEY_C;
        case 'd': case 'D': return Arcade::Event::ARC_KEY_D;
        case 'e': case 'E': return Arcade::Event::ARC_KEY_E;
        case 'f': case 'F': return Arcade::Event::ARC_KEY_F;
        case 'g': case 'G': return Arcade::Event::ARC_KEY_G;
        case 'h': case 'H': return Arcade::Event::ARC_KEY_H;
        case 'i': case 'I': return Arcade::Event::ARC_KEY_I;
        case 'j': case 'J': return Arcade::Event::ARC_KEY_J;
        case 'k': case 'K': return Arcade::Event::ARC_KEY_K;
        case 'l': case 'L': return Arcade::Event::ARC_KEY_L;
        case 'm': case 'M': return Arcade::Event::ARC_KEY_M;
        case 'n': case 'N': return Arcade::Event::ARC_KEY_N;
        case 'o': case 'O': return Arcade::Event::ARC_KEY_O;
        case 'p': case 'P': return Arcade::Event::ARC_KEY_P;
        case 'q': case 'Q': return Arcade::Event::ARC_KEY_Q;
        case 'r': case 'R': return Arcade::Event::ARC_KEY_R;
        case 's': case 'S': return Arcade::Event::ARC_KEY_S;
        case 't': case 'T': return Arcade::Event::ARC_KEY_T;
        case 'u': case 'U': return Arcade::Event::ARC_KEY_U;
        case 'v': case 'V': return Arcade::Event::ARC_KEY_V;
        case 'w': case 'W': return Arcade::Event::ARC_KEY_W;
        case 'x': case 'X': return Arcade::Event::ARC_KEY_X;
        case 'y': case 'Y': return Arcade::Event::ARC_KEY_Y;
        case 'z': case 'Z': return Arcade::Event::ARC_KEY_Z;
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

        case KEY_F(1):  return Arcade::Event::ARC_KEY_F1;
        case KEY_F(2):  return Arcade::Event::ARC_KEY_F2;
        case KEY_F(3):  return Arcade::Event::ARC_KEY_F3;
        case KEY_F(4):  return Arcade::Event::ARC_KEY_F4;
        case KEY_F(5):  return Arcade::Event::ARC_KEY_F5;
        case KEY_F(6):  return Arcade::Event::ARC_KEY_F6;
        case KEY_F(7):  return Arcade::Event::ARC_KEY_F7;
        case KEY_F(8):  return Arcade::Event::ARC_KEY_F8;
        case KEY_F(9):  return Arcade::Event::ARC_KEY_F9;
        case KEY_F(10): return Arcade::Event::ARC_KEY_F10;
        case KEY_F(11): return Arcade::Event::ARC_KEY_F11;
        case KEY_F(12): return Arcade::Event::ARC_KEY_F12;

        case KEY_UP:    return Arcade::Event::ARC_ARROW_UP;
        case KEY_DOWN:  return Arcade::Event::ARC_ARROW_DOWN;
        case KEY_LEFT:  return Arcade::Event::ARC_ARROW_LEFT;
        case KEY_RIGHT: return Arcade::Event::ARC_ARROW_RIGHT;

        case KEY_BACKSPACE:
        case 127:        return Arcade::Event::ARC_KEY_BACKSPACE;

        case KEY_ENTER:
        case '\n':
        case '\r':      return Arcade::Event::ARC_KEY_RETURN;

        case ' ':        return Arcade::Event::ARC_KEY_SPACE;
        case '\t':      return Arcade::Event::ARC_KEY_TAB;
        case 27:         return Arcade::Event::ARC_KEY_ESC;
        case KEY_RESIZE: return Arcade::Event::ARC_RESIZE;

        default:        return {};
    }
}
