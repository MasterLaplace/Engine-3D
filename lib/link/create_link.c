/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** create_link
*/

#include "linkList.h"

link_t *create_link(void *new)
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
