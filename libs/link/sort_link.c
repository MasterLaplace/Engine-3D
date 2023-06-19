/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** sort_link
*/

#include "link_list.h"

static void split_list(link_t *head, unsigned len_list, link_t **left, link_t **right)
{
    link_t *slow_ptr = head;

    for (register unsigned i = 0; i < len_list/2 && slow_ptr; i++)
        slow_ptr = slow_ptr->next;

    *left = head;
    *right = slow_ptr->next;
    slow_ptr->next = NULL;
}

static link_t *merge(link_t *left, link_t *right, bool (*cmp)(void *, void *))
{
    link_t *result = NULL;

    if (left == NULL)
        return right;
    else if (right == NULL)
        return left;

    if (cmp((void *)left->obj, (void *)right->obj)) {
        result = left;
        result->next = merge(left->next, right, cmp);
    } else {
        result = right;
        result->next = merge(left, right->next, cmp);
    }
    return result;
}

static void merge_sort(link_t **list, unsigned len_list, bool (*cmp)(void *, void *))
{
    link_t *left = NULL;
    link_t *right = NULL;

    if (*list == NULL || (*list)->next == NULL)
        return;

    split_list(*list, len_list, &left, &right);

    merge_sort(&left, len_list/2, cmp);
    merge_sort(&right, len_list/2, cmp);

    *list = merge(left, right, cmp);
}

void merge_sort_list(link_t **list, unsigned len_list, bool (*cmp)(void *, void *))
{
    if (*list == NULL || (*list)->next == NULL)
        return;
    (*list)->prev->next = NULL;
    merge_sort(list, len_list, cmp);

    link_t *actual = (*list);
    link_t *prev = NULL;

    while ((*list) && actual) {
        prev = actual;
        if (actual->next == NULL) {
            actual->next = (*list);
            (*list)->prev = actual;
            break;
        }
        actual = actual->next;
        actual->prev = prev;
    }
}
