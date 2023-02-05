/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** clean
*/

#include "engine.h"

void clean_mesh()
{
    if (!LIST_OBJS)
        return;
    while (LIST_OBJS) {
        while ((triangle_t *)((mesh_t *) LIST_OBJS->obj)->lTriangle) {
            free((triangle_t *)((mesh_t *) LIST_OBJS->obj)->lTriangle->obj);
            list_remove(&(((mesh_t *) LIST_OBJS->obj)->lTriangle), ((mesh_t *) LIST_OBJS->obj)->lTriangle);
        }
        free((mesh_t *) LIST_OBJS->obj);
        list_remove(&(LIST_OBJS), LIST_OBJS);
    }
}

void destroying()
{
    clean_mesh();
}
