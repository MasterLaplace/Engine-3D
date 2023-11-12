/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** engine_event
*/

#ifndef ENGINE_EVENT_H_
    #define ENGINE_EVENT_H_
////////////////////////////////////////////////////////////
// Include the appropriate header based on the platform used
////////////////////////////////////////////////////////////
#include "config.h"
#include "engine_renderer.h"
#include "event_keyboard.h"

////////////////////////////////////////////////////////////
// Include the necessary headers for the event module
////////////////////////////////////////////////////////////
#ifdef __cplusplus
    #include <cstdlib>

    using namespace std;
    extern "C" {
#else
    #include <stdlib.h>
#endif

typedef struct {
    union {
        event_keyboard_t keyboard;
        // event_mouse_t mouse;
        // event_joystick_t joystick;
    } event;
    void (*event_callback)(void);
} event_callback_t;

#define EVENT_CALLBACKS_COUNT KEYBOARD_SIZE // + MOUSE_SIZE // + JOYSTICK_SIZE

typedef struct engine_event_s {
    event_callback_t event_callback[EVENT_CALLBACKS_COUNT];
#if GRAPHICS_LIBRARY == CSFML
    sfEvent graphics_event;
#elif GRAPHICS_LIBRARY == SFML && defined(__cplusplus)
    sf::Event graphics_event;
#elif GRAPHICS_LIBRARY == SDL
    SDL_Event graphics_event;
#endif
} engine_event_t;

engine_event_t *event_create(void);

extern void event_add_keyboard_callback(engine_event_t *event, event_keyboard_t keyboard, void (*event_callback)(void));

extern void event_remove_keyboard_callback(engine_event_t *event, event_keyboard_t keyboard);

extern void event_update(engine_event_t *event, engine_renderer_t *renderer);

extern void event_destroy(engine_event_t *event);

#endif /* !ENGINE_EVENT_H_ */
