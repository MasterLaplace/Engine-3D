/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** window
*/

#ifndef WINDOW_H_
    #define WINDOW_H_

////////////////////////////////////////////////////////////
// Include the Engine module header for the window module
////////////////////////////////////////////////////////////
#include "config.h"
#include "engine_math.h"

////////////////////////////////////////////////////////////
// Include necessary headers for the window module
////////////////////////////////////////////////////////////
#ifdef __cplusplus
    #include <cstdbool>
#else
    #include <stdbool.h>
#endif

/**
 * @brief  Structure containing the window module of the engine
 *
 * @param window The window of the game engine
 */
typedef struct {
    #if GRAPHICS_LIBRARY == CSFML
        sfRenderWindow *window;
    #elif GRAPHICS_LIBRARY == SFML
        sf::RenderWindow *window;
    #elif GRAPHICS_LIBRARY == SDL
        SDL_Window *window;
        SDL_Renderer *renderer;
    #elif GRAPHICS_LIBRARY == OPENGL
        GL_Window *window;
    #elif GRAPHICS_LIBRARY == VULKAN
        VK_Window *window;
    #elif GRAPHICS_LIBRARY == DIRECTX
        DX_Window *window;
    #endif
} engine_window_t;

/**
 * @brief  Create a window module
 *
 * @param title {char *} - The title of the window
 * @param width {unsigned} - The width of the window
 * @param height {unsigned} - The height of the window
 * @return {engine_window_t *} - The window module
 */
extern engine_window_t *window_create(const char *title, unsigned width, unsigned height);

/**
 * @brief  Destroy a window module
 *
 * @param window {engine_window_t *} - The window module
 */
extern void window_destroy(engine_window_t *window);

/**
 * @brief  Check if the window is open
 *
 * @param window {engine_window_t *} - The window module
 * @return {bool} - The status of the window
 */
extern bool window_is_open(engine_window_t *window);

/**
 * @brief  Close the window
 *
 * @param window {engine_window_t *} - The window module
 */
extern void window_close(engine_window_t *window);

/**
 * @brief  Clear the window
 *
 * @param window {engine_window_t *} - The window module
 */
extern void window_clear(engine_window_t *window);

/**
 * @brief  Display the window
 *
 * @param window {engine_window_t *} - The window module
 */
extern void window_display(engine_window_t *window);

/**
 * @brief  Get the size of the window
 *
 * @param window {engine_window_t *} - The window module
 * @return {point_f} - The size of the window
 */
extern point_f window_get_size(engine_window_t *window);

/**
 * @brief  Get the position of the window
 *
 * @param window {engine_window_t *} - The window module
 * @return {point_f} - The position of the window
 */
extern point_f window_get_position(engine_window_t *window);

/**
 * @brief  Set the position of the window
 *
 * @param window {engine_window_t *} - The window module
 * @param position {point_f} - The position of the window
 */
extern void window_set_position(engine_window_t *window, point_f position);

/**
 * @brief  Set the size of the window
 *
 * @param window {engine_window_t *} - The window module
 * @param size {point_f} - The size of the window
 */
extern void window_set_size(engine_window_t *window, point_f size);

/**
 * @brief  Set the title of the window
 *
 * @param window {engine_window_t *} - The window module
 * @param title {char *} - The title of the window
 */
extern void window_set_title(engine_window_t *window, const char *title);

#endif /* !WINDOW_H_ */
