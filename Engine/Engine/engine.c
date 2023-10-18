/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-17
** File description:
** engine
*/

#include "engine.h"

engine_t *engine_init(const char *title, unsigned width, unsigned height)
{
    engine_t *engine = malloc(sizeof(engine_t));

    engine->clock = clock_create();
    engine->window = window_create(title, width, height);
    return engine;
}

void engine_destroy(engine_t *engine)
{
    clock_destroy(engine->clock);
    window_destroy(engine->window);
    free(engine);
}
