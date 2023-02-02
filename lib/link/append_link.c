/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** append_link
*/

#include "linkList.h"

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
