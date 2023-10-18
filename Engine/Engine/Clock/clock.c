/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** clock
*/

#include "engine_clock.h"

engine_clock_t *clock_create(void)
{
    engine_clock_t *clock = (engine_clock_t*)malloc(sizeof(engine_clock_t));
    #if GRAPHICS_LIBRARY == CSFML
        clock->clock = sfClock_create();
    #elif GRAPHICS_LIBRARY == SFML
        clock->clock = new sf::Clock();
    #elif GRAPHICS_LIBRARY == SDL
        clock->clock = SDL_CreateClock();
    #elif GRAPHICS_LIBRARY == OPENGL
        clock->clock = GL_CreateClock();
    #elif GRAPHICS_LIBRARY == VULKAN
        clock->clock = VK_CreateClock();
    #endif
    return clock;
}

void clock_destroy(engine_clock_t *clock)
{
    #if GRAPHICS_LIBRARY == CSFML
        sfClock_destroy(clock->clock);
    #elif GRAPHICS_LIBRARY == SFML
        delete clock->clock;
    #elif GRAPHICS_LIBRARY == SDL
        SDL_DestroyClock(clock->clock);
    #elif GRAPHICS_LIBRARY == OPENGL //using glwf for opengl and vulkan
        GL_DestroyClock(clock->clock);
    #elif GRAPHICS_LIBRARY == VULKAN
        VK_DestroyClock(clock->clock);
    #elif GRAPHICS_LIBRARY == DIRECTX
        DX_DestroyClock(clock->clock);
    #endif
    free(clock);
}

void clock_restart(engine_clock_t *clock)
{
    #if GRAPHICS_LIBRARY == CSFML
        sfClock_restart(clock->clock);
    #elif GRAPHICS_LIBRARY == SFML
        clock->clock->restart();
    #elif GRAPHICS_LIBRARY == SDL
        SDL_RestartClock(clock->clock);
    #elif GRAPHICS_LIBRARY == OPENGL
        GL_RestartClock(clock->clock);
    #elif GRAPHICS_LIBRARY == VULKAN
        VK_RestartClock(clock->clock);
    #elif GRAPHICS_LIBRARY == DIRECTX
        DX_RestartClock(clock->clock);
    #endif
}

float clock_get_f_delta_time(engine_clock_t *clock)
{
    #if GRAPHICS_LIBRARY == CSFML
        float delta_time = sfTime_asSeconds(sfClock_getElapsedTime(clock->clock));
        return sfClock_restart(clock->clock), delta_time;
    #elif GRAPHICS_LIBRARY == SFML
        float delta_time = clock->clock->getElapsedTime().asSeconds();
        return clock->clock->restart().asSeconds(), delta_time;
    #elif GRAPHICS_LIBRARY == SDL
        float delta_time = SDL_GetElapsedTime(clock->clock);
        return SDL_RestartClock(clock->clock), delta_time;
    #elif GRAPHICS_LIBRARY == OPENGL
        float delta_time = GL_GetElapsedTime(clock->clock);
        return GL_RestartClock(clock->clock), delta_time;
    #elif GRAPHICS_LIBRARY == VULKAN
        float delta_time = VK_GetElapsedTime(clock->clock);
        return VK_RestartClock(clock->clock), delta_time;
    #elif GRAPHICS_LIBRARY == DIRECTX
        float delta_time = DX_GetElapsedTime(clock->clock);
        return DX_RestartClock(clock->clock), delta_time;
    #endif
}
