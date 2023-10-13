/*
** EPITECH PROJECT, 2023
** Title: Laplace Link Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_do
*/

#include "laplace_link.h"

void laplace_link_do(link_t *list, void (*func)(void *))
{
    link_t *actual = list;

    if (!actual)
        return;
    do {
        func(actual->obj);
        actual = actual->next;
    } while (list && actual != list);
}
