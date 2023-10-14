/*
** EPITECH PROJECT, 2023
** Title: Laplace Map Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-14
** File description:
** map_create
*/

#include "laplace_map.h"

map_t *laplace_map_create(void *key, void *obj)
{
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return (NULL);

    map->key = key;
    map->obj = obj;
    map->next = NULL;

    return map;
}
