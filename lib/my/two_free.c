/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** two_free
*/

#include "my.h"

void two_free(char **tab)
{
    if (!tab || !*tab)
        return;

    for (size_t i = 0; i < two_len(tab); ++i)
        free(tab[i]);
    free(tab);
}
