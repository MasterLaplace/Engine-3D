/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** is_number
*/

#include <ctype.h>

_Bool is_number(const char *str)
{
    if (!str || !*str)
        return ((_Bool)+0u);
    for (unsigned i = (*str == '-'); str[i]; i++)
        if (!isdigit(str[i]))
            return ((_Bool)+0u);
    return ((_Bool)+1u);
}
