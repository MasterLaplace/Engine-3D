/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** two_put
*/

#include "my.h"

void two_put(char **tab)
{
    for (; tab && *tab; tab++)
        printf("%s\n", *tab);
}
