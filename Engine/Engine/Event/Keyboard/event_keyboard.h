/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-11-11
** File description:
** event_keyboard
*/

#ifndef EVENT_KEYBOARD_H_
    #define EVENT_KEYBOARD_H_

////////////////////////////////////////////////////////////
// Include the appropriate header based on the platform used
////////////////////////////////////////////////////////////
#include "config.h"

enum key_state {
    KEY_PRESSED,
    KEY_RELEASED,
    KEY_STATE_SIZE
};

enum key_code {
    KEY_UNKNOWN,
    KEY_SPACE,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_ESCAPE,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP,
    KEY_CODE_SIZE
};

#define KEYBOARD_SIZE KEY_CODE_SIZE * KEY_STATE_SIZE

typedef struct keyboard_event_s {
    enum key_code key_code;
    enum key_state key_state;
} event_keyboard_t;

#include "engine_event.h"

typedef struct engine_event_s engine_event_t;

extern void keyboard_graphics_to_engine(engine_event_t *event);

#endif /* !EVENT_KEYBOARD_H_ */
