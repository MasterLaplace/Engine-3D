/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** sort_link
*/

#include "link_list.h"

static void split_list(link_t *head, link_t **left, link_t **right)
{
    link_t *slow_ptr = head;
    link_t *fast_ptr = head->next;

    while (fast_ptr != NULL) {
        fast_ptr = fast_ptr->next;
        if (fast_ptr != NULL) {
            slow_ptr = slow_ptr->next;
            fast_ptr = fast_ptr->next;
        }
    }

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

static void merge_sort(link_t **list, bool (*cmp)(void *, void *))
{
    link_t *left = NULL;
    link_t *right = NULL;

    if (*list == NULL || (*list)->next == NULL)
        return;

    split_list(*list, &left, &right);

    merge_sort(&left, cmp);
    merge_sort(&right, cmp);

    *list = merge(left, right, cmp);
}

void merge_sort_list(link_t **list, bool (*cmp)(void *, void *))
{
    if (*list == NULL || (*list)->next == NULL)
        return;
    (*list)->prev->next = NULL;
    merge_sort(list, cmp);

    link_t *actual = (*list);
    link_t *prev = NULL;

    while ((*list) && actual) {
        prev = actual;
        if (actual->next == NULL) {
            actual->next = (*list);
            (*list)->prev = actual;
            return;
        }
        actual = actual->next;
        actual->prev = prev;
    }
}
