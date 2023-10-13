/*
** EPITECH PROJECT, 2023
** Title: Laplace Link Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_get_at_index
*/

#include "laplace_link.h"

link_t *laplace_link_get_at_index(link_t *link, unsigned index)
{
    link_t *actual = link;

    if (!actual)
        return (NULL);
    for (unsigned i = 0; i < index; ++i) {
        actual = actual->next;
        if (actual == link)
            return (NULL);
    }
    return actual;
}
