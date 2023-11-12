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
#include "engine_renderer.h"
#include "engine_event.h"
#include "engine_math.h"

/**
 * @brief  Structure containing the engine module
 *
 * @param clock {engine_clock_t *} - The clock module
 * @param renderer {engine_renderer_t *} - The renderer module
 * @param event {event_t *} - The event module
 * @return {engine_t *} - The engine module
 */
typedef struct {
    engine_clock_t *clock;
    engine_renderer_t *renderer;
    engine_event_t *event;
} engine_t;

/**
 * @brief  Initialize the engine module
 *
 * @param config_file {const char *} - The config file path
 * @param width {unsigned} - The width of the window (default: 1920)
 * @param height {unsigned} - The height of the window (default: 1080)
 * @param vr {bool} - The vr mode (default: false)
 * @return {engine_t *} - The engine module
 */
extern engine_t *engine_init(const char *config_file, unsigned width, unsigned height, bool vr);

/**
 * @brief  Check if the engine is running
 *
 * @param engine {engine_t *} - The engine module
 * @return true {bool} - If the engine is running
 * @return false {bool} - If the engine is not running
 */
extern bool engine_is_running(engine_t *engine);

/**
 * @brief  Handle the events of the engine module
 *
 * @param engine {engine_t *} - The engine module
 */
extern void engine_event(engine_t *engine);

/**
 * @brief  Update the engine module (physics, AI, etc.)
 *
 * @param engine {engine_t *} - The engine module
 */
extern void engine_update(engine_t *engine);

/**
 * @brief  Render the engine module (rendering)
 *
 * @param engine {engine_t *} - The engine module
 */
extern void engine_render(engine_t *engine);

/**
 * @brief  Destroy the engine module
 *
 * @param engine {engine_t *} - The engine module
 */
extern void engine_destroy(engine_t *engine);

#endif /* !ENGINE_H_ */
