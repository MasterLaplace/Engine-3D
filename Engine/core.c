/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-16
** File description:
** core
*/

#include "engine.h"
#include <stdio.h>

#ifdef ENGINE_SYSTEM_WINDOWS
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main(int ac, const char *av[]) {
#endif
    // Initialize the game engine and its components.
    if (ac != 2) {
        printf("Usage: ./engine.out [config.xml]\n");
        return EXIT_FAILURE;
    }
    printf("Loading config file: %s\n", av[1]);
    printf("Engine version: %s\n", ENGINE_VERSION_STRING);
    engine_t *engine = engine_init(av[1], 600, 600, true); // using the xml_parser to load the config file
    if (engine == NULL)
        return EXIT_FAILURE;

    // Game loop
    while (engine_is_running(engine)) {
        // Handle events (e.g., user input, window events).
        engine_event(engine);

        // Update the game world, physics, AI, etc.
        // add update injector here
        engine_update(engine);

        // Render the game.
        engine_render(engine);
    }

    // Clean up resources and perform any necessary shutdown tasks.
    engine_destroy(engine);

    return EXIT_SUCCESS;
}
