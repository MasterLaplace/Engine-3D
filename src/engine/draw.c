/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** draw
*/

#include "engine.h"

void display_triangles(link_t *mesh)
{
    sfVertexArray *vertex_array = NULL;
    link_t *actual = mesh;
    triangle_t *node = NULL;

    if (!actual)
        return;
    do {
        node = (triangle_t *) actual->obj;

        if (node->sommet[0].x >= WIN_X || node->sommet[0].x < 0 || node->sommet[0].y >= WIN_Y || node->sommet[0].y < 0
            || node->sommet[1].x >= WIN_X || node->sommet[1].x < 0 || node->sommet[1].y >= WIN_Y || node->sommet[1].y < 0
            || node->sommet[2].x >= WIN_X || node->sommet[2].x < 0 || node->sommet[2].y >= WIN_Y || node->sommet[2].y < 0)
            goto next;
        vertex_array = create_triangle(
            (sfVector2f){node->sommet[0].x, node->sommet[0].y},
            (sfVector2f){node->sommet[1].x, node->sommet[1].y},
            (sfVector2f){node->sommet[2].x, node->sommet[2].y}
        );
        sfRenderWindow_drawVertexArray(WINDOW, vertex_array, NULL);
        sfVertexArray_destroy(vertex_array);
    next:
        actual = actual->next;
    } while (mesh && actual->next != mesh);
}
