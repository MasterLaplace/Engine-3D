/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** char_in_list
*/

#include "my.h"

int char_in_list(char c, char *list)
{
    for (int i = 0; list[i]; ++i) {
        if (c == list[i])
            return i;
    }
    return (-1);
}
