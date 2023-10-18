/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** engine_clock
*/

#ifndef ENGINE_CLOCK_H_
    #define ENGINE_CLOCK_H_

////////////////////////////////////////////////////////////
// Include the other headers of the engine module
////////////////////////////////////////////////////////////
#include "config.h"

////////////////////////////////////////////////////////////
// Include the necessary headers for the clock module
////////////////////////////////////////////////////////////
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

/**
 * @brief  Structure containing the clock module
 *
 * @param clock The clock of the clock module
 * @return {clock_t *} - The clock module
 */
typedef struct {
    #if GRAPHICS_LIBRARY == CSFML
        sfClock *clock;
    #elif GRAPHICS_LIBRARY == SFML
        sf::Clock *clock;
    #elif GRAPHICS_LIBRARY == SDL
        SDL_Clock *clock;
    #elif GRAPHICS_LIBRARY == OPENGL
        GL_Clock *clock;
    #elif GRAPHICS_LIBRARY == VULKAN
        VK_Clock *clock;
    #elif GRAPHICS_LIBRARY == DIRECTX
        DX_Clock *clock;
    #endif
} engine_clock_t;

/**
 * @brief  Create a clock module
 *
 * @return {engine_clock_t *} - The clock module
 */
extern engine_clock_t *clock_create(void);

/**
 * @brief  Destroy a clock module
 *
 * @param clock {engine_clock_t *} - The clock module
 */
extern void clock_destroy(engine_clock_t *clock);

/**
 * @brief  Get the delta time of a clock module
 *
 * @param clock {engine_clock_t *} - The clock module
 * @return {float} - The delta time
 */
extern float clock_get_f_delta_time(engine_clock_t *clock);

#endif /* !ENGINE_CLOCK_H_ */
