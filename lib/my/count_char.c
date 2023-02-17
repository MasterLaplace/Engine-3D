/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** count_char
*/

#include "my.h"

size_t count_char(char const *str, char c)
{
    size_t nb = 0;

    for (; str[nb]; (str[nb] == c) ? nb++ : *str++);
    return nb;
}
