/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** two_free
*/

#include <stdlib.h>

void my_free(char **to_free) { free(*to_free); }

void two_free(char **tab)
{
    if (!tab)
        return;
    for (unsigned i = 0; tab[i]; i++) {
        free(tab[i]);
        tab[i] = NULL;
    }
    free(tab);
    tab = NULL;
}
