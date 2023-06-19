/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** do_link
*/

#include "link_list.h"

void do_list(link_t *list, void (*func)(void *))
{
    link_t *actual = list;

    if (!actual)
        return;
    do {
        func(actual->obj);
        actual = actual->next;
    } while (list && actual != list);
}
