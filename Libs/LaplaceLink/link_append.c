/*
** EPITECH PROJECT, 2023
** Title: Laplace Link Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_append
*/

#include "laplace_link.h"

void laplace_link_append(link_t **list, link_t *link)
{
    link_t *start = NULL;

    if (!link)
        return;
    if (!list || !*list) {
        link->next = link;
        link->prev = link;
        *list = link;
        return;
    }
    start = *(list);
    link->prev = start->prev;
    (start->prev)->next = link;
    start->prev = link;
    link->next = *list;
}
