/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** dup_list
*/

#include "link_list.h"
#include <string.h>

link_t *dup_list(link_t *list, unsigned __size)
{
    link_t *new = NULL;
    link_t *actual = list;
    typeof(__size) *tmp = NULL;

    if (!actual)
        return (NULL);
    do {
        tmp = malloc(__size);
        memcpy(tmp, actual->obj, __size);
        list_append(&new, create_link(tmp));
        actual = actual->next;
    } while (list && actual != list);
    return new;
}
