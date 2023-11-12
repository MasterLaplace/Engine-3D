/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-19
** File description:
** engine_renderer
*/

#ifndef ENGINE_RENDERER_H_
    #define ENGINE_RENDERER_H_

////////////////////////////////////////////////////////////
// Include the appropriate header based on the platform used
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Include the other headers of the engine module
////////////////////////////////////////////////////////////
#include "render_window.h"

/**
 * @brief  Structure containing the engine module
 *
 * @param window {render_window_t *} - The window module
 * @param vr_mode {bool} - The vr mode state (true if vr mode is enabled)
 * @return {engine_renderer_t *} - The engine module
 */
typedef struct {
    render_window_t *window;
    bool vr_mode;
} engine_renderer_t;

/**
 * @brief  Initialize the renderer module
 *
 * @param title {const char *} - The title of the window
 * @param width {unsigned} - The width of the window
 * @param height {unsigned} - The height of the window
 * @param vr_mode {bool} - The vr mode state (true if vr mode is enabled)
 * @return {engine_renderer_t *} - The renderer module
 */
extern engine_renderer_t *renderer_init(const char *title, unsigned width, unsigned height, bool vr_mode);

extern bool renderer_is_open(engine_renderer_t *renderer);

/**
 * @brief  Clear the renderer module
 *
 * @param renderer {engine_renderer_t *} - The renderer module
 */
extern void renderer_clear(engine_renderer_t *renderer);

/**
 * @brief  Display the renderer module
 *
 * @param renderer {engine_renderer_t *} - The renderer module
 */
extern void renderer_display(engine_renderer_t *renderer);

/**
 * @brief  Destroy the renderer module
 *
 * @param renderer {engine_renderer_t *} - The renderer module
 */
extern void renderer_destroy(engine_renderer_t *renderer);

#endif /* !ENGINE_RENDERER_H_ */
