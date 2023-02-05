/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** core
*/

#include "engine.h"

engine_t engine;

void init(void) __attribute__((constructor));
void clean(void) __attribute__((destructor));

void init(void)
{
    if (!open_folder( "./assets/obj_examples/" ))
        exit(EXIT_FAILURE);
}

void clean(void)
{
    destroying();
}

static void manage_triangle(mesh_t *mesh)
{
    link_t *actual = mesh->lTriangle;
    triangle_t *tetrimi = NULL;
    sizint i = 0;

    if (!actual)
        return;
    do {
        tetrimi = (triangle_t *) actual->obj;
        printf("%d: [0] (%.1f, %.1f, %.1f) | ", i, tetrimi->sommet[0].x, tetrimi->sommet[0].y, tetrimi->sommet[0].z);
        printf("[1] (%.1f, %.1f, %.1f) | ", tetrimi->sommet[1].x, tetrimi->sommet[1].y, tetrimi->sommet[1].z);
        printf("[2] (%.1f, %.1f, %.1f)\n", tetrimi->sommet[2].x, tetrimi->sommet[2].y, tetrimi->sommet[2].z);
        i++;
        actual = actual->next;
    } while (mesh->lTriangle && actual != mesh->lTriangle);
}

static void draw_mesh(void)
{
    link_t *actual = engine.list_objs;
    mesh_t *tetrimi = NULL;

    if (!actual)
        return;
    do {
        tetrimi = (mesh_t *) actual->obj;
        manage_triangle(tetrimi);
        actual = actual->next;
    } while (engine.list_objs && actual != engine.list_objs);
}

int main()
{
    draw_mesh();
    return EXIT_SUCCESS;
}
