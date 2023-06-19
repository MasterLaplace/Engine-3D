/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** swap_link
*/

#include "link_list.h"

void swap_link(link_t **start, link_t *left, link_t *right)
{
    link_t *prev_left = left->prev;
    link_t *next_right = right->next;

    prev_left->next = right;
    next_right->prev = left;
    right->next = left;
    right->prev = prev_left;
    left->prev = right;
    left->next = next_right;

    if (*start == left)
        *start = right;
    else if (*start == right)
        *start = left;
}
