/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** two_put
*/

#include <stdio.h>

void two_put(const char *tab[])
{
    if (!tab)
        return;
    for (; *tab; ++tab)
        printf("%s\n", *tab);
}
