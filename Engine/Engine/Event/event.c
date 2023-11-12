/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-11-12
** File description:
** event
*/

#include "engine_event.h"

engine_event_t *event_create(void)
{
    engine_event_t *event = calloc(1, sizeof(engine_event_t));

    if (event == NULL)
        return (NULL);
    return (event);
}

void event_add_keyboard_callback(engine_event_t *event, event_keyboard_t keyboard, void (*event_callback)(void))
{
    if (keyboard.key_code <= KEY_UNKNOWN || keyboard.key_code >= KEY_CODE_SIZE)
        return;
    unsigned i = keyboard.key_code - 1 * KEY_STATE_SIZE + keyboard.key_state;
    event->event_callback[i].event.keyboard = keyboard;
    event->event_callback[i].event_callback = event_callback;
}

void event_remove_keyboard_callback(engine_event_t *event, event_keyboard_t keyboard)
{
    if (keyboard.key_code <= KEY_UNKNOWN || keyboard.key_code >= KEY_CODE_SIZE)
        return;
    unsigned i = keyboard.key_code - 1 * KEY_STATE_SIZE + keyboard.key_state;
    event->event_callback[i].event.keyboard.key_code = 0;
    event->event_callback[i].event_callback = NULL;
}

#if GRAPHICS_LIBRARY == CSFML /* do not use elsewhere */
    #define EVENT_GET_ALL sfRenderWindow_pollEvent(renderer->window->window, &(event->graphics_event))
    #define EVENT_GET_TYPE type
    #define EVENT_TYPE_CLOSE sfEvtClosed
    #define EVENT_ESCAPE_CLOSE sfKeyboard_isKeyPressed(sfKeyEscape)
#elif GRAPHICS_LIBRARY == SFML && defined(__cplusplus) /* do not use elsewhere */
    #define EVENT_GET_ALL renderer->window->window->pollEvent(graphics_event)
    #define EVENT_GET_TYPE type
    #define EVENT_TYPE_CLOSE sf::Event::Closed
    #define EVENT_ESCAPE_CLOSE sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
#elif GRAPHICS_LIBRARY == SDL /* do not use elsewhere */
    #define EVENT_GET_ALL SDL_PollEvent(&graphics_event)
    #define EVENT_GET_TYPE type
    #define EVENT_TYPE_CLOSE SDL_QUIT
    #define EVENT_ESCAPE_CLOSE (event->graphics_event.key.keysym.sym == SDLK_ESCAPE)
#endif

void event_update(engine_event_t *event, engine_renderer_t *renderer)
{
    while (EVENT_GET_ALL) {
        if (event->graphics_event.EVENT_GET_TYPE == EVENT_TYPE_CLOSE || EVENT_ESCAPE_CLOSE) {
            window_close(renderer->window);
            return;
        }
        keyboard_graphics_to_engine(event);
    }
}

void event_destroy(engine_event_t *event)
{
    free(event);
}
