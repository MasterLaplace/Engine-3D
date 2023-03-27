/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** strcat
*/

#include "my.h"

char *my_strcat(char const *dest, char const *src)
{
    char *tmp = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 1));
    size_t i = 0;
    size_t e = 0;

    if (!dest || !src || !tmp)
        return (NULL);

    for (; src[i]; ++i)
        tmp[i] = src[i];
    for (; dest[e]; ++i, ++e)
        tmp[i] = dest[e];
    tmp[i] = '\0';
    return tmp;
}
