/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** append_link
*/

#include "link_list.h"

void list_append(link_t **list, link_t *link)
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
