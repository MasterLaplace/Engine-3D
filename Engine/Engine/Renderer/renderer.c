/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-22
** File description:
** renderer
*/

#include "engine_renderer.h"

engine_renderer_t *renderer_init(const char *title, unsigned width, unsigned height, bool vr_mode)
{
    engine_renderer_t *renderer = malloc(sizeof(engine_renderer_t));

    if (renderer == NULL)
        return (NULL);
    if ((renderer->window = window_create(title, width, height)) == NULL)
        return (NULL);
    renderer->vr_mode = vr_mode;
    return renderer;
}

bool renderer_is_open(engine_renderer_t *renderer)
{
    return window_is_open(renderer->window);
}

void renderer_clear(engine_renderer_t *renderer)
{
    window_clear(renderer->window);
}

void renderer_display(engine_renderer_t *renderer)
{
    window_display(renderer->window);
}

void renderer_destroy(engine_renderer_t *renderer)
{
    window_destroy(renderer->window);
    free(renderer);
}
