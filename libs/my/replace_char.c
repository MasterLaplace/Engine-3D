/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** replace_char
*/

#include <string.h>

void replace_char(char *str, char orig, char rep)
{
    char *ix = str;

    if (!str || !*str || !orig)
        return;
    for (unsigned n = 0; (ix = strchr(ix, orig)); n++) {
        *ix++ = rep;
    }
}
