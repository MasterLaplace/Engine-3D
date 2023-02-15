/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** merge_sort
*/

#include "engine.h"

static bool cmp_two_triangles(triangle_t *t1, triangle_t *t2)
{
    float z1 = (t1->sommet[0].z + t1->sommet[1].z + t1->sommet[2].z) / 3.0f;
    float z2 = (t2->sommet[0].z + t2->sommet[1].z + t2->sommet[2].z) / 3.0f;
    return z1 > z2;
}

static void splitList(link_t *head, link_t **left, link_t **right)
{
    link_t *sh_next;
    link_t *sh_middle;
    link_t *end;
    sh_middle = head;
    sh_next = head->next;

    while (sh_next != NULL) {
        if (sh_next->next == NULL)
            end = sh_next;
        sh_next = sh_next->next;
        if (sh_next != NULL) {
            sh_middle = sh_middle->next;
            if (sh_next->next == NULL)
                end = sh_next;
            sh_next = sh_next->next;
        }
    }

    (*right) = sh_middle->next;
    end->next = NULL;
    sh_middle->next = NULL;
    (*left) = head;
}

static link_t *merge(link_t *left, link_t *right) {
    link_t *result = NULL;

    if (left == NULL)
        return right;
    else if (right == NULL)
        return left;

    if (cmp_two_triangles((triangle_t *)left->obj, (triangle_t *)right->obj)) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

static void mergeSort(link_t **list)
{
    link_t *left = NULL;
    link_t *right = NULL;

    if (*list == NULL || (*list)->next == NULL)
        return;

    splitList(*list, &left, &right);

    mergeSort(&left);
    mergeSort(&right);

    *list = merge(left, right);
}

void merge_sorting_list(link_t **list)
{
    if (*list == NULL || (*list)->next == NULL)
        return;
    (*list)->prev->next = NULL;

    mergeSort(list);

    link_t *actual = (*list);
    link_t *prev = NULL;

    if (!actual)
        return;
    while ((*list) && actual != NULL) {
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
