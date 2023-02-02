/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** remove_link
*/

#include "linkList.h"

void list_remove(link_t **list, link_t *link)
{
    if (!list || !*(list) || !link)
        return;
    if (link->next == link) {
        *list = NULL;
        free(link);
        link = NULL;
        return;
    }
    if (link == *list)
        *list = (*list)->next;
    (link->next)->prev = link->prev;
    (link->prev)->next = link->next;
    free(link);
}
