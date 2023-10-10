/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** strcat
*/

#include <string.h>
#include <stdlib.h>

char *my_strcat(char const *dest, char const *src)
{
    char *tmp = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 1));
    unsigned i = 0;
    unsigned e = 0;

    if (!tmp)
        return (NULL);

    for (; src && src[i]; ++i)
        tmp[i] = src[i];
    for (; dest && dest[e]; ++i, ++e)
        tmp[i] = dest[e];
    tmp[i] = '\0';
    return tmp;
}
