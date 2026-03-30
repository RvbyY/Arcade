/*
** EPITECH PROJECT, 2026
** Project - Arcade
** File description:
** Header file for
** libarcade's events
*/

#pragma once


namespace Arcade {
    inline namespace Events {
        /**
         * A key event should be triggered
         * when the specified key is being
         * held down at the time of polling.
         *
         * This means key events are interpreted
         * as key "presses", not key "releases".
         *
         * Note:
         * All events under `misc` are NOT
         * real events. The `COUNT` value
         * represents the amount of different
         * event types that exist.
         */
        enum Event {
            // letter keys
            ARC_KEY_A, ARC_KEY_B, ARC_KEY_C, ARC_KEY_D, ARC_KEY_E, ARC_KEY_F,
            ARC_KEY_G, ARC_KEY_H, ARC_KEY_I, ARC_KEY_J, ARC_KEY_K, ARC_KEY_L,
            ARC_KEY_M, ARC_KEY_N, ARC_KEY_O, ARC_KEY_P, ARC_KEY_Q, ARC_KEY_R,
            ARC_KEY_S, ARC_KEY_T, ARC_KEY_U, ARC_KEY_V, ARC_KEY_W, ARC_KEY_X,
            ARC_KEY_Y, ARC_KEY_Z,

            // digit keys
            ARC_KEY_1, ARC_KEY_2, ARC_KEY_3, ARC_KEY_4, ARC_KEY_5, ARC_KEY_6,
            ARC_KEY_7, ARC_KEY_8, ARC_KEY_9, ARC_KEY_0,

            // function keys
            ARC_KEY_F1, ARC_KEY_F2, ARC_KEY_F3, ARC_KEY_F4, ARC_KEY_F5,
            ARC_KEY_F6, ARC_KEY_F7, ARC_KEY_F8, ARC_KEY_F9, ARC_KEY_F10,
            ARC_KEY_F11, ARC_KEY_F12,

            // arrow keys
            ARC_ARROW_UP,
            ARC_ARROW_DOWN,
            ARC_ARROW_LEFT,
            ARC_ARROW_RIGHT,

            // control keys
            ARC_KEY_BACKSPACE,
            ARC_KEY_RETURN,
            ARC_KEY_SPACE,
            ARC_KEY_SHIFT,
            ARC_KEY_CTRL,
            ARC_KEY_ALT,
            ARC_KEY_TAB,
            ARC_KEY_ESC,

            // mouse evts
            ARC_MOUSE_RIGHT_CLICK,
            ARC_MOUSE_LEFT_CLICK,
            ARC_MOUSE_MOVE,

            // control evts
            ARC_RESIZE,
            ARC_CLOSE,

            // misc
            ARC_COUNT,  // keep last
        };
    }
}
