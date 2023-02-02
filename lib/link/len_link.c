/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** len_link
*/

#include "linkList.h"

size_t len_link(link_t *link)
{
    link_t *actual = link;
    size_t count = 0;

    if (!actual)
        return count;
    do {
        count++;
        actual = actual->next;
    } while (link && actual != link);
    return count;
}
