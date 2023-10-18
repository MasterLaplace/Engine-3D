/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** engine
*/

#ifndef ENGINE_H_
    #define ENGINE_H_

////////////////////////////////////////////////////////////
// Include the appropriate header based on the platform used
////////////////////////////////////////////////////////////
#include "config.h"

////////////////////////////////////////////////////////////
// Include the other headers of the engine module
////////////////////////////////////////////////////////////
#include "engine_clock.h"
#include "engine_window.h"
#include "engine_math.h"

/**
 * @brief  Structure containing the engine module
 *
 * @param clock {engine_clock_t *} - The clock module
 * @param window {window_t *} - The window module
 * @return {engine_t *} - The engine module
 */
typedef struct {
    engine_clock_t *clock;
    engine_window_t *window;
} engine_t;

/**
 * @brief  Initialize the engine module
 *
 * @return {engine_t *} - The engine module
 */
extern engine_t *engine_init(const char *title, unsigned width, unsigned height);

/**
 * @brief  Destroy the engine module
 *
 * @param engine {engine_t *} - The engine module
 */
extern void engine_destroy(engine_t *engine);

#endif /* !ENGINE_H_ */
