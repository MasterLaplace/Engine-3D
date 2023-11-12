/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-17
** File description:
** engine
*/

#include "engine.h"

engine_t *engine_init(const char *title, unsigned width, unsigned height, bool vr)
{
    engine_t *engine = malloc(sizeof(engine_t));

    if (engine == NULL)
        return (NULL);
    if ((engine->clock = clock_create()) == NULL)
        return (NULL);
    if ((engine->renderer = renderer_init(title, width, height, vr)) == NULL)
        return (NULL);
    if ((engine->event = event_create()) == NULL)
        return (NULL);
    return engine;
}

bool engine_is_running(engine_t *engine)
{
    return renderer_is_open(engine->renderer);
}

void engine_event(engine_t *engine)
{
    event_update(engine->event, engine->renderer);
}

void engine_update(engine_t *engine)
{
    float deltatime = clock_get_f_delta_time(engine->clock);
    (void) deltatime;
}

void engine_render(engine_t *engine)
{
    renderer_clear(engine->renderer);
    renderer_display(engine->renderer);
}

void engine_destroy(engine_t *engine)
{
    clock_destroy(engine->clock);
    renderer_destroy(engine->renderer);
    event_destroy(engine->event);
    free(engine);
}
