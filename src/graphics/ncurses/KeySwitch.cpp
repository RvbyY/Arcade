#include "include/graphics/ncurses/Ncurses.hpp"

std::optional<Arcade::Event> switchCaseKey(int ch)
{
    switch (ch) {
        case 'a':       return Arcade::Event::KEY_A;
        case 'b':       return Arcade::Event::KEY_B;
        case 'c':       return Arcade::Event::KEY_C;
        case 'd':       return Arcade::Event::KEY_D;
        case 'e':       return Arcade::Event::KEY_E;
        case 'f':       return Arcade::Event::KEY_F;
        case 'g':       return Arcade::Event::KEY_G;
        case 'h':       return Arcade::Event::KEY_H;
        case 'i':       return Arcade::Event::KEY_I;
        case 'j':       return Arcade::Event::KEY_J;
        case 'k':       return Arcade::Event::KEY_K;
        case 'l':       return Arcade::Event::KEY_L;
        case 'm':       return Arcade::Event::KEY_M;
        case 'n':       return Arcade::Event::KEY_N;
        case 'o':       return Arcade::Event::KEY_O;
        case 'p':       return Arcade::Event::KEY_P;
        case 'q':       return Arcade::Event::KEY_Q;
        case 'r':       return Arcade::Event::KEY_R;
        case 's':       return Arcade::Event::KEY_S;
        case 't':       return Arcade::Event::KEY_T;
        case 'u':       return Arcade::Event::KEY_U;
        case 'v':       return Arcade::Event::KEY_V;
        case 'w':       return Arcade::Event::KEY_W;
        case 'x':       return Arcade::Event::KEY_X;
        case 'y':       return Arcade::Event::KEY_Y;
        case 'z':       return Arcade::Event::KEY_Z;
        case '1':       return Arcade::Event::KEY_1;
        case '2':       return Arcade::Event::KEY_2;
        case '3':       return Arcade::Event::KEY_3;
        case '4':       return Arcade::Event::KEY_4;
        case '5':       return Arcade::Event::KEY_5;
        case '6':       return Arcade::Event::KEY_6;
        case '7':       return Arcade::Event::KEY_7;
        case '8':       return Arcade::Event::KEY_8;
        case '9':       return Arcade::Event::KEY_9;
        case '0':       return Arcade::Event::KEY_0;
        default:        return {};
    }
}