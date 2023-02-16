/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** count_char
*/

#include "my.h"

size_t count_char(char const *str, char c)
{
    size_t nbr = 0;

    if (!str)
        return (0);

    for (size_t i = 0; i < strlen(str); i++)
        if (str[i] == c)
            nbr++;
    return nbr;
}
