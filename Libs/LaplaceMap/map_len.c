/*
** EPITECH PROJECT, 2023
** Title: Laplace Map Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-14
** File description:
** map_len
*/

#include "laplace_map.h"

unsigned laplace_map_len(map_t *map)
{
    unsigned len = 0;

    while (map)
        len++, map = map->next;

    return len;
}
