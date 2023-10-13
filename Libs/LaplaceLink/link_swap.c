/*
** EPITECH PROJECT, 2023
** Title: Laplace Link Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_swap
*/

#include "laplace_link.h"

void laplace_link_swap(link_t **start, link_t *left, link_t *right)
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
