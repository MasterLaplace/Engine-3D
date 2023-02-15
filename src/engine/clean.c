/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** clean
*/

#include "engine.h"

void clean_triangles(link_t *mesh)
{
    if (!mesh)
        return;
    while (mesh) {
        free((triangle_t *) mesh->obj);
        list_remove(&(mesh), mesh);
    }
}

void clean_mesh()
{
    if (!LIST_OBJS)
        return;
    while (LIST_OBJS) {
        clean_triangles((link_t *)((mesh_t *) LIST_OBJS->obj)->lTriangle);
        free((mesh_t *) LIST_OBJS->obj);
        list_remove(&(LIST_OBJS), LIST_OBJS);
    }
}

void destroying()
{
    sfClock_destroy(engine.clock);
    sfRenderWindow_destroy(WINDOW);
    clean_mesh();
}
