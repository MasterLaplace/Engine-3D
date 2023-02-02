/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** find_str
*/

#include "my.h"

bool find_str(char *str, const char *src)
{
    sizint len = strlen(src);

    for (sizint i = 0; i < strlen(str); i++) {
        if (!strncmp(&str[i], src, len))
            return true;
    }
    return false;
}
