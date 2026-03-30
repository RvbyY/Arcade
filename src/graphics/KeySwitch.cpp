#include "include/graphics/ncurses/Ncurses.hpp"

std::optional<Arcade::Event> switchCaseKey(int ch)
{
    switch (ch) {
        case 'a':       return Arcade::Event::ARC_KEY_A;
        case 'b':       return Arcade::Event::ARC_KEY_B;
        case 'c':       return Arcade::Event::ARC_KEY_C;
        case 'd':       return Arcade::Event::ARC_KEY_D;
        case 'e':       return Arcade::Event::ARC_KEY_E;
        case 'f':       return Arcade::Event::ARC_KEY_F;
        case 'g':       return Arcade::Event::ARC_KEY_G;
        case 'h':       return Arcade::Event::ARC_KEY_H;
        case 'i':       return Arcade::Event::ARC_KEY_I;
        case 'j':       return Arcade::Event::ARC_KEY_J;
        case 'k':       return Arcade::Event::ARC_KEY_K;
        case 'l':       return Arcade::Event::ARC_KEY_L;
        case 'm':       return Arcade::Event::ARC_KEY_M;
        case 'n':       return Arcade::Event::ARC_KEY_N;
        case 'o':       return Arcade::Event::ARC_KEY_O;
        case 'p':       return Arcade::Event::ARC_KEY_P;
        case 'q':       return Arcade::Event::ARC_KEY_Q;
        case 'r':       return Arcade::Event::ARC_KEY_R;
        case 's':       return Arcade::Event::ARC_KEY_S;
        case 't':       return Arcade::Event::ARC_KEY_T;
        case 'u':       return Arcade::Event::ARC_KEY_U;
        case 'v':       return Arcade::Event::ARC_KEY_V;
        case 'w':       return Arcade::Event::ARC_KEY_W;
        case 'x':       return Arcade::Event::ARC_KEY_X;
        case 'y':       return Arcade::Event::ARC_KEY_Y;
        case 'z':       return Arcade::Event::ARC_KEY_Z;
        case '1':       return Arcade::Event::ARC_KEY_1;
        case '2':       return Arcade::Event::ARC_KEY_2;
        case '3':       return Arcade::Event::ARC_KEY_3;
        case '4':       return Arcade::Event::ARC_KEY_4;
        case '5':       return Arcade::Event::ARC_KEY_5;
        case '6':       return Arcade::Event::ARC_KEY_6;
        case '7':       return Arcade::Event::ARC_KEY_7;
        case '8':       return Arcade::Event::ARC_KEY_8;
        case '9':       return Arcade::Event::ARC_KEY_9;
        case '0':       return Arcade::Event::ARC_KEY_0;
        default:        return {};
    }
}