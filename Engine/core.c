/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-16
** File description:
** core
*/

#include <stdio.h>
#include <stdlib.h>

#ifdef ENGINE_SYSTEM_WINDOWS
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main(int ac, const char *av[]) {
#endif
    if (ac != 2) {
        printf("Usage: ./engine.out [config.xml]\n");
        return EXIT_FAILURE;
    }
    printf("Loading config file: %s\n", av[1]);
    return EXIT_SUCCESS;
}
