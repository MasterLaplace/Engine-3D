/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** count_char
*/

#include <stddef.h>

unsigned count_char(char const *str, char c)
{
    unsigned nb = 0;

    if (!str)
        return nb;
    for (; str[nb]; (str[nb] == c) ? nb++ : *str++);
    return nb;
}
