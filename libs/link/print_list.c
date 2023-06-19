/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** print_list
*/

#include "link_list.h"

void print_list(link_t *list, void (*print)(void *))
{
    link_t *actual = list;

    if (!actual)
        return;
    do {
        print(actual->obj);
        actual = actual->next;
    } while (list && actual != list);
}
