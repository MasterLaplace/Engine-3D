/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** draw
*/

#include "engine.h"


static sfVertexArray *create_triangle(triangle_t *node)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1, vertex2, vertex3;

    int lighting = (int)(node->dp * 255);
    if (color < 50)
        color = 50;

    if (node->usemtl == WATER || node->usemtl == BUBBLE) {
        sfColor color = (sfColor){lighting, lighting, lighting, 255/1.5};
        vertex1 = (sfVertex){*(sfVector2f*)&(node->sommet[0]), color, *(sfVector2f*)&(node->texture[0])};
        vertex2 = (sfVertex){*(sfVector2f*)&(node->sommet[1]), color, *(sfVector2f*)&(node->texture[1])};
        vertex3 = (sfVertex){*(sfVector2f*)&(node->sommet[2]), color, *(sfVector2f*)&(node->texture[2])};
    } else if (node->usemtl != NONE) {
        sfColor color = (sfColor){lighting, lighting, lighting, 255};
        sfVector2u texSize = sfTexture_getSize(engine.textures[node->usemtl]->texture);
        vertex1 = (sfVertex){*(sfVector2f*)&(node->sommet[0]), color, (sfVector2f){node->texture[0].x * texSize.x, node->texture[0].y * texSize.y}};
        vertex2 = (sfVertex){*(sfVector2f*)&(node->sommet[1]), color, (sfVector2f){node->texture[1].x * texSize.x, node->texture[1].y * texSize.y}};
        vertex3 = (sfVertex){*(sfVector2f*)&(node->sommet[2]), color, (sfVector2f){node->texture[2].x * texSize.x, node->texture[2].y * texSize.y}};
    } else {
        sfColor color = (sfColor){lighting, lighting, lighting, 255};
        vertex1 = (sfVertex){*(sfVector2f*)&(node->sommet[0]), .color = color};
        vertex2 = (sfVertex){*(sfVector2f*)&(node->sommet[1]), .color = color};
        vertex3 = (sfVertex){*(sfVector2f*)&(node->sommet[2]), .color = color};
    }

    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_append(vertex_array, vertex3);
    sfVertexArray_setPrimitiveType(vertex_array, sfTriangleFan);
    return vertex_array;
}

void display_triangles(link_t *mesh)
{
    sfVertexArray *vertex_array = NULL;
    link_t *actual = mesh;
    triangle_t *node = NULL;

    if (!actual)
        return;
    do {
        node = (triangle_t *) actual->obj;

        if ((vertex_array = create_triangle(node))) {
            if (node->usemtl != NONE)
                sfRenderWindow_drawVertexArray(WINDOW, vertex_array, engine.textures[node->usemtl]);
            else
        sfRenderWindow_drawVertexArray(WINDOW, vertex_array, NULL);
        sfVertexArray_destroy(vertex_array);
        }
        actual = actual->next;
    } while (mesh && actual->next != mesh);
}
