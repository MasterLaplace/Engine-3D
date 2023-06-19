/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** getnbr
*/

#include <ctype.h>

unsigned getnbr(char const *str)
{
    unsigned exp = 0;

    if (!str)
        return exp;

    for (unsigned i = (*str == '-'); isdigit(str[i]); i++)
        exp = exp * 10 + str[i] - '0';
    if ((*str == '-'))
        exp *= -1;
    return exp;
}
