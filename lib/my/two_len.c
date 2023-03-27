/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** two_len
*/

#include "my.h"

size_t two_len(char **tab)
{
    size_t i = 0;

    if (!tab)
        return i;

    for (; tab[i]; ++i);
    return i;
}
