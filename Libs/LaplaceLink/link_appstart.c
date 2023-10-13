/*
** EPITECH PROJECT, 2023
** Title: Laplace Link Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_appstart
*/

#include "laplace_link.h"

void laplace_link_appstart(link_t **list, link_t *link)
{
    link_t *start = *list;
    link_t *end = (*list)->prev;

    end->next = link;
    start->prev = link;
    link->prev = end;
    link->next = start;
    *list = link;
}
