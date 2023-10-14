/*
** EPITECH PROJECT, 2023
** Title: Laplace Map Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-14
** File description:
** map_appstart
*/

#include "laplace_map.h"

void laplace_map_appstart(map_t **list, map_t *map)
{
    if (!*list && (*list = map))
        return;

    map->next = *list;
    *list = map;
}
