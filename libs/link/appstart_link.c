/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** appstart_link
*/

#include "link_list.h"

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
