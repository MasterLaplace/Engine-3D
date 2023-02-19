/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** core
*/

#include "engine.h"

engine_t engine;

void init(void) __attribute__((constructor));
void clean(void) __attribute__((destructor));

void init(void)
{
    if (!open_folder( "./assets/obj_examples/" ))
        exit(EXIT_FAILURE);
    if (!init_engine())
        exit(EXIT_FAILURE);
}

void clean(void)
{
    destroying();
}

int main(int ac, char const *av[])
{
    if (print_help(ac, av))
        return EXIT_SUCCESS;
    loop_engine();
    return EXIT_SUCCESS;
}
