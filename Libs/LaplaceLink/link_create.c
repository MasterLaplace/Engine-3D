/*
** EPITECH PROJECT, 2023
** Title: Laplace Link Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_create
*/

#include "laplace_link.h"

link_t *laplace_link_create(void *new)
{
    link_t *link = malloc(sizeof(link_t));

    if (!link || !new)
        return (NULL);
    if (new)
        link->obj = new;
    link->next = link;
    link->prev = link;
    return link;
}
