/*
** EPITECH PROJECT, 2023
** Title: Laplace Map Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-14
** File description:
** map_get_at_key
*/

#include "laplace_map.h"

map_t *laplace_map_get_at_key(map_t *list, void *key, bool (*cmp)(void *, void *))
{
    while (list && cmp(list->key, key))
        list = list->next;
    return list;
}
