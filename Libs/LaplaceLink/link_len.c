/*
** EPITECH PROJECT, 2023
** Title: Laplace Link Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_len
*/

#include "laplace_link.h"

unsigned laplace_link_len(link_t *link)
{
    link_t *actual = link;
    unsigned count = 0;

    if (!actual)
        return count;
    do {
        count++;
        actual = actual->next;
    } while (link && actual != link);
    return count;
}
