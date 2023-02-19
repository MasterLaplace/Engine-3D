/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** Bounding Volume Hierarchy
*/

#include "engine.h"

static sfVector3f average_triangle(triangle_t *t)
{
    float x = (t->sommet[0].x + t->sommet[1].x + t->sommet[2].x) / 3.0f;
    float y = (t->sommet[0].y + t->sommet[1].y + t->sommet[2].y) / 3.0f;
    float z = (t->sommet[0].z + t->sommet[1].z + t->sommet[2].z) / 3.0f;
    return (sfVector3f){x, y, z};
}

static void cmp_triangles(triangle_t *triangle, triangle_t *smaller, triangle_t *greater)
{
    for (sizint i = 0; i < 3; i++) {
        greater->sommet[i].x = fmax(triangle->sommet[i].x,greater->sommet[i].x);
        greater->sommet[i].y = fmax(triangle->sommet[i].y, greater->sommet[i].y);
        greater->sommet[i].z = fmax(triangle->sommet[i].z, greater->sommet[i].z);

        smaller->sommet[i].x = fmin(triangle->sommet[i].x, smaller->sommet[i].x);
        smaller->sommet[i].y = fmin(triangle->sommet[i].y, smaller->sommet[i].y);
        smaller->sommet[i].z = fmin(triangle->sommet[i].z, smaller->sommet[i].z);
    }
}

void set_bvh(link_t *mesh)
{
    link_t *actual = mesh;
    triangle_t *node = NULL;
    triangle_t S_G[2];

    memset(&S_G, 0, sizeof(S_G));
    if (!actual)
        return;
    do {
        node = (triangle_t *) actual->obj;
        cmp_triangles(node, &S_G[0], &S_G[1]);
        actual = actual->next;
    } while (mesh && actual->next != mesh);

    engine.s_g[0] = average_triangle(&S_G[0]);
    engine.s_g[1] = average_triangle(&S_G[1]);
}
