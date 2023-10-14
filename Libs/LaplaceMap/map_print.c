/*
** EPITECH PROJECT, 2023
** Title: Laplace Map Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-14
** File description:
** map_print
*/

#include "laplace_map.h"

void laplace_map_print(map_t *list, void (*print)(map_t *))
{
    printf("[map_t]:\n");
    while (list) {
        print(list);
        list = list->next;
    }
}
