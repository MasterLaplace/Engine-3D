/*
** EPITECH PROJECT, 2023
** Title: Laplace Link Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_get_at_obj
*/

#include "laplace_link.h"

link_t *laplace_link_get_at_obj(link_t *link, void *obj)
{
    link_t *actual = link;

    if (!actual)
        return (NULL);
    do {
        if (actual->obj == obj)
            return (actual);
        actual = actual->next;
    } while (actual != link);
    return (NULL);
}
