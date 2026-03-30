/*
** EPITECH PROJECT, 2026
** Project - Arcade
** File description:
** Header file for
** libarcade's events
*/

#pragma once


namespace Arcade {
    /**
     * A key event should be triggered
     * when the specified key is being
     * held down at the time of polling.
     *
     * This means key events are interpreted
     * as key "presses", not key "releases".
     */
    enum class Event {
        // letter keys
        KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F,
        KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L,
        KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R,
        KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X,
        KEY_Y, KEY_Z,

        // digit keys
        KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6,
        KEY_7, KEY_8, KEY_9, KEY_0,

        // control keys
        KEY_BACKSPACE,
        KEY_RETURN,
        KEY_SPACE,
        KEY_SHIFT,
        KEY_CTRL,
        KEY_ALT,
        KEY_TAB,
        KEY_ESC,

        // mouse evts
        MOUSE_RIGHT_CLICK,
        MOUSE_LEFT_CLICK,
        MOUSE_MOVE,

        // control evts
        RESIZE,
        CLOSE,

        // misc
        COUNT,  // keep last
    };
}
