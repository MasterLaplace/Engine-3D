/*
** EPITECH PROJECT, 2023
** Title: Laplace Map Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-14
** File description:
** map_append
*/

#include "laplace_map.h"

void laplace_map_append(map_t **list, map_t *map)
{
    if (!*list && (*list = map))
        return;

    map_t *tmp = *list;

    while (tmp->next)
        tmp = tmp->next;

    tmp->next = map;
}
