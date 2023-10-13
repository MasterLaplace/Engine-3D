/*
** EPITECH PROJECT, 2023
** Title: Laplace Link Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_dup
*/

#include "laplace_link.h"

#ifdef __cplusplus
    #include <ccstring>
#else
    #include <string.h>
#endif

link_t *laplace_link_dup(link_t *list, unsigned __size)
{
    link_t *new = NULL;
    link_t *actual = list;
    typeof(__size) *tmp = NULL;

    if (!actual)
        return (NULL);
    do {
        tmp = malloc(__size);
        memcpy(tmp, actual->obj, __size);
        laplace_link_append(&new, laplace_link_create(tmp));
        actual = actual->next;
    } while (list && actual != list);
    return new;
}
