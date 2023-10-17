/*
** EPITECH PROJECT, 2023
** Title: Laplace Link Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_remove
*/

#include "laplace_link.h"

void laplace_link_remove(link_t **list, link_t *link, void (*free_data)(void *))
{
    if (!list || !*(list) || !link)
        return;
    if (link->next == link) {
        if (free_data)
            free_data(link->obj);
        free(link);
        *list = NULL;
        return;
    }
    if (link == *list)
        *list = (*list)->next;
    (link->next)->prev = link->prev;
    (link->prev)->next = link->next;
    if (free_data)
        free_data(link->obj);
    free(link);
}
