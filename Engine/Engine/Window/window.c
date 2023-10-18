/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** window
*/

#include "engine_window.h"

engine_window_t *window_create(const char *title, unsigned width, unsigned height)
{
    engine_window_t *window = malloc(sizeof(engine_window_t));

    if (!window)
        return (NULL);

    #if GRAPHICS_LIBRARY == CSFML
        window->window = sfRenderWindow_create((sfVideoMode){width, height, 32}, title, sfDefaultStyle, NULL);
    #elif GRAPHICS_LIBRARY == SFML
        window->window = new sf::RenderWindow(sf::VideoMode(width, height, 32), title.c_str());
    #elif GRAPHICS_LIBRARY == SDL
        SDL_Init(SDL_INIT_VIDEO);
        if (!(window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN))) {
            SDL_Quit();
            free(window);
            return (NULL);
        }
        if (!(window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED))) {
            SDL_DestroyWindow(window->window);
            SDL_Quit();
            free(window);
            return (NULL);
        }
        SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
    #elif GRAPHICS_LIBRARY == OPENGL
        window->window = glCreateWindow(
            title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, SDL_WINDOW_SHOWN);
    #elif GRAPHICS_LIBRARY == VULKAN
        window->window = vkCreateWindow(
            title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, SDL_WINDOW_SHOWN);
    #endif

    if (!window->window) {
        free(window);
        return (NULL);
    }
    return window;
}

void window_destroy(engine_window_t *window)
{
    #if GRAPHICS_LIBRARY == CSFML
        sfRenderWindow_destroy(window->window);
    #elif GRAPHICS_LIBRARY == SFML
        delete window->window;
    #elif GRAPHICS_LIBRARY == SDL
        SDL_DestroyRenderer(window->renderer);
        SDL_DestroyWindow(window->window);
        SDL_Quit();
    #elif GRAPHICS_LIBRARY == OPENGL
    #endif
}

bool window_is_open(engine_window_t *window)
{
    #if GRAPHICS_LIBRARY == CSFML
        return sfRenderWindow_isOpen(window->window);
    #elif GRAPHICS_LIBRARY == SFML
        return window->window->isOpen();
    #elif GRAPHICS_LIBRARY == SDL
        return true;
    #elif GRAPHICS_LIBRARY == OPENGL
    #endif
}

void window_close(engine_window_t *window)
{
    #if GRAPHICS_LIBRARY == CSFML
        sfRenderWindow_close(window->window);
    #elif GRAPHICS_LIBRARY == SFML
        window->window->close();
    #elif GRAPHICS_LIBRARY == OPENGL
    #endif
}

void window_clear(engine_window_t *window)
{
    #if GRAPHICS_LIBRARY == CSFML
        sfRenderWindow_clear(window->window, sfBlack);
    #elif GRAPHICS_LIBRARY == SFML
        window->window->clear(sf::Color::Black);
    #elif GRAPHICS_LIBRARY == SDL
        SDL_RenderClear(window->renderer);
    #endif
}

void window_display(engine_window_t *window)
{
    #if GRAPHICS_LIBRARY == CSFML
        sfRenderWindow_display(window->window);
    #elif GRAPHICS_LIBRARY == SFML
        window->window->display();
    #elif GRAPHICS_LIBRARY == SDL
        SDL_RenderPresent(window->renderer);
    #endif
}

point_f window_get_size(engine_window_t *window)
{
    #if GRAPHICS_LIBRARY == CSFML
        sfVector2u size = sfRenderWindow_getSize(window->window);
        return (point_f){size.x, size.y};
    #elif GRAPHICS_LIBRARY == SFML
        sf::Vector2u size = window->window->getSize();
        return (point_f){size.x, size.y};
    #elif GRAPHICS_LIBRARY == SDL
        int w, h;
        SDL_GetWindowSize(window->window, &w, &h);
        return (point_f){w, h};
    #elif GRAPHICS_LIBRARY == OPENGL
    #endif
}

point_f window_get_position(engine_window_t *window)
{
    #if GRAPHICS_LIBRARY == CSFML
        sfVector2i position = sfRenderWindow_getPosition(window->window);
        return (point_f){position.x, position.y};
    #elif GRAPHICS_LIBRARY == SFML
        sf::Vector2i position = window->window->getPosition();
        return (point_f){position.x, position.y};
    #elif GRAPHICS_LIBRARY == SDL
        int x, y;
        SDL_GetWindowPosition(window->window, &x, &y);
        return (point_f){x, y};
    #elif GRAPHICS_LIBRARY == OPENGL
    #endif
}

void window_set_position(engine_window_t *window, point_f position)
{
    #if GRAPHICS_LIBRARY == CSFML
        sfRenderWindow_setPosition(window->window, (sfVector2i){position.x, position.y});
    #elif GRAPHICS_LIBRARY == SFML
        window->window->setPosition(sf::Vector2i(position.x, position.y));
    #elif GRAPHICS_LIBRARY == SDL
        SDL_SetWindowPosition(window->window, (int)position.x, (int)position.y);
    #endif
}

void window_set_size(engine_window_t *window, point_f size)
{
    #if GRAPHICS_LIBRARY == CSFML
        sfRenderWindow_setSize(window->window, (sfVector2u){size.x, size.y});
    #elif GRAPHICS_LIBRARY == SFML
        window->window->setSize(sf::Vector2u(size.x, size.y));
    #elif GRAPHICS_LIBRARY == SDL
        SDL_SetWindowSize(window->window, (int)size.x, (int)size.y);
    #endif
}

void window_set_title(engine_window_t *window, const char *title)
{
    #if GRAPHICS_LIBRARY == CSFML
        sfRenderWindow_setTitle(window->window, title);
    #elif GRAPHICS_LIBRARY == SFML
        window->window->setTitle(title.c_str());
    #elif GRAPHICS_LIBRARY == SDL
        SDL_SetWindowTitle(window->window, title);
    #endif
}
