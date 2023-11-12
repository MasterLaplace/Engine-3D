/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-11-12
** File description:
** keyboard
*/

#include "event_keyboard.h"

#if GRAPHICS_LIBRARY == CSFML
    #define KEYBOARD_EVENT sfEvent
    #define KEYBOARD_GET_TYPE type
    #define KEYBOARD_TYPE_PRESSED sfEvtKeyPressed
    #define KEYBOARD_TYPE_RELEASED sfEvtKeyReleased
    #define GRAPHICS_CODE_TO_ENGINE_CODE keyboard_code_csfml_to_engine

static enum key_code keyboard_code_csfml_to_engine(KEYBOARD_EVENT graphics_event)
{
    if (graphics_event.key.code == sfKeySpace)
        return (KEY_SPACE);
    if (graphics_event.key.code >= sfKeyNum0 && graphics_event.key.code <= sfKeyNum9)
        return (KEY_0 + graphics_event.key.code - sfKeyNum0);
    if (graphics_event.key.code >= sfKeyA && graphics_event.key.code <= sfKeyZ)
        return (KEY_A + graphics_event.key.code - sfKeyA);
    if (graphics_event.key.code == sfKeyEscape)
        return (KEY_ESCAPE);
    if (graphics_event.key.code >= sfKeyRight && graphics_event.key.code <= sfKeyUp)
        return (KEY_RIGHT + graphics_event.key.code - sfKeyRight);
    return (KEY_UNKNOWN);
}

#elif GRAPHICS_LIBRARY == SFML && defined(__cplusplus)
    #define KEYBOARD_EVENT sf::Event
    #define KEYBOARD_GET_TYPE type
    #define KEYBOARD_TYPE_PRESSED sf::Event::KeyPressed
    #define KEYBOARD_TYPE_RELEASED sf::Event::KeyReleased
    #define GRAPHICS_CODE_TO_ENGINE_CODE keyboard_code_sfml_to_engine

static enum key_code keyboard_code_sfml_to_engine(KEYBOARD_EVENT graphics_event)
{
    if (graphics_event.key.code == sf::Keyboard::Space)
        return (KEY_SPACE);
    if (graphics_event.key.code >= sf::Keyboard::Num0 && graphics_event.key.code <= sf::Keyboard::Num9)
        return (KEY_0 + graphics_event.key.code - sf::Keyboard::Num0);
    if (graphics_event.key.code >= sf::Keyboard::A && graphics_event.key.code <= sf::Keyboard::Z)
        return (KEY_A + graphics_event.key.code - sf::Keyboard::A);
    if (graphics_event.key.code == sf::Keyboard::Escape)
        return (KEY_ESCAPE);
    if (graphics_event.key.code >= sf::Keyboard::Right && graphics_event.key.code <= sf::Keyboard::Up)
        return (KEY_RIGHT + graphics_event.key.code - sf::Keyboard::Right);
    return (KEY_UNKNOWN);
}

#elif GRAPHICS_LIBRARY == SDL
    #define KEYBOARD_EVENT SDL_Event
    #define KEYBOARD_GET_TYPE key.state
    #define KEYBOARD_TYPE_PRESSED SDL_PRESSED
    #define KEYBOARD_TYPE_RELEASED SDL_RELEASED
    #define GRAPHICS_CODE_TO_ENGINE_CODE keyboard_code_sdl_to_engine

static enum key_code keyboard_code_sdl_to_engine(KEYBOARD_EVENT graphics_event)
{
    if (graphics_event.key.keysym.sym == SDLK_SPACE)
        return (KEY_SPACE);
    if (graphics_event.key.keysym.sym >= SDLK_0 && graphics_event.key.keysym.sym <= SDLK_9)
        return (KEY_0 + graphics_event.key.keysym.sym - SDLK_0);
    if (graphics_event.key.keysym.sym >= SDLK_a && graphics_event.key.keysym.sym <= SDLK_z)
        return (KEY_A + graphics_event.key.keysym.sym - SDLK_a);
    if (graphics_event.key.keysym.sym == SDLK_ESCAPE)
        return (KEY_ESCAPE);
    if (graphics_event.key.keysym.sym >= SDLK_RIGHT && graphics_event.key.keysym.sym <= SDLK_UP)
        return (KEY_RIGHT + graphics_event.key.keysym.sym - SDLK_RIGHT);
    return (KEY_UNKNOWN);
}

#endif

void keyboard_graphics_to_engine(engine_event_t *event)
{
    if (event->graphics_event.KEYBOARD_GET_TYPE == KEYBOARD_TYPE_PRESSED) {
        unsigned i = GRAPHICS_CODE_TO_ENGINE_CODE(event->graphics_event) * KEY_STATE_SIZE + KEY_PRESSED;
        if (i - KEY_PRESSED == KEY_UNKNOWN)
            return;
        event->event_callback[i].event_callback();
    }
    if (event->graphics_event.KEYBOARD_GET_TYPE == KEYBOARD_TYPE_RELEASED) {
        unsigned i = GRAPHICS_CODE_TO_ENGINE_CODE(event->graphics_event) * KEY_STATE_SIZE + KEY_RELEASED;
        if (i - KEY_RELEASED == KEY_UNKNOWN)
            return;
        event->event_callback[i].event_callback();
    }
}
