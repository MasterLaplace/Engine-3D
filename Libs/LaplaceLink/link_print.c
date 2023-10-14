/*
** EPITECH PROJECT, 2023
** Title: Laplace Link Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_print
*/

#include "laplace_link.h"

void laplace_link_print(link_t *list, void (*print)(void *))
{
    link_t *actual = list;

    printf("[link_t]:\n");
    if (!actual)
        return;
    do {
        print(actual->obj);
        actual = actual->next;
    } while (list && actual != list);
}
