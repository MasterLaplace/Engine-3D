/*
** EPITECH PROJECT, 2023
** Title: Laplace Map Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-14
** File description:
** map_remove
*/

#include "laplace_map.h"

void laplace_map_remove(map_t **list, map_t *map, void (*clean_data)(map_t *map))
{
    if (!*list)
        return;

    if (*list == map) {
        *list = (*list)->next;
        clean_data(map);
        free(map);
        return;
    }

    map_t *tmp = *list;

    while (tmp->next) {
        if (tmp->next == map) {
            tmp->next = tmp->next->next;
            clean_data(map);
            free(map);
            return;
        }
        tmp = tmp->next;
    }
}
