/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** appstart_link
*/

#include "linkList.h"

void appstart_link(link_t **list, link_t *link)
{
    link_t *start = *list;
    link_t *end = (*list)->prev;

    end->next = link;
    start->prev = link;
    link->prev = end;
    link->next = start;
    *list = link;
}
