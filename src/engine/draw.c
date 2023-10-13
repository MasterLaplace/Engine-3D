/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** draw
*/

#include "engine.h"

// void TexturedTriangle(triangle_t * tri,
//     int x1, int y1, float u1, float v1, float w1,
//     int x2, int y2, float u2, float v2, float w2,
//     int x3, int y3, float u3, float v3, float w3,
// 	const sfImage *image, sfVector2u texSize)
// {
//     if (tri->sommet[1].y < tri->sommet[0].y) {
//         SWAP(tri->sommet[0].y, tri->sommet[1].y);
//         SWAP(tri->sommet[0].x, tri->sommet[1].x);
//         SWAP(u1, u2);
//         SWAP(v1, v2);
//         SWAP(w1, w2);
//     }

//     if (y3 < y1) {
//         SWAP(y1, y3);
//         SWAP(x1, x3);
//         SWAP(u1, u3);
//         SWAP(v1, v3);
//         SWAP(w1, w3);
//     }

//     if (y3 < y2) {
//         SWAP(y2, y3);
//         SWAP(x2, x3);
//         SWAP(u2, u3);
//         SWAP(v2, v3);
//         SWAP(w2, w3);
//     }

//     int dy1 = y2 - y1;
//     int dx1 = x2 - x1;
//     float dv1 = v2 - v1;
//     float du1 = u2 - u1;
//     float dw1 = w2 - w1;

//     int dy2 = y3 - y1;
//     int dx2 = x3 - x1;
//     float dv2 = v3 - v1;
//     float du2 = u3 - u1;
//     float dw2 = w3 - w1;

//     float texture_u, texture_v, texture_w;

//     float dax_step, dbx_step, du1_step, dv1_step, du2_step, dv2_step, dw1_step, dw2_step = 0;

//     if (dy1) dax_step = dx1 / (float)abs(dy1);
//     if (dy2) dbx_step = dx2 / (float)abs(dy2);

//     if (dy1) du1_step = du1 / (float)abs(dy1);
//     if (dy1) dv1_step = dv1 / (float)abs(dy1);
//     if (dy1) dw1_step = dw1 / (float)abs(dy1);

//     if (dy2) du2_step = du2 / (float)abs(dy2);
//     if (dy2) dv2_step = dv2 / (float)abs(dy2);
//     if (dy2) dw2_step = dw2 / (float)abs(dy2);

//     if (dy1) {
//         for (register int i = y1; i <= y2; i++) {
//             int ax = x1 + (float)(i - y1) * dax_step;
//             int bx = x1 + (float)(i - y1) * dbx_step;

//             float texture_su = u1 + (float)(i - y1) * du1_step;
//             float texture_sv = v1 + (float)(i - y1) * dv1_step;
//             float texture_sw = w1 + (float)(i - y1) * dw1_step;

//             float texture_eu = u1 + (float)(i - y1) * du2_step;
//             float texture_ev = v1 + (float)(i - y1) * dv2_step;
//             float texture_ew = w1 + (float)(i - y1) * dw2_step;

//             if (ax > bx) {
//                 SWAP(ax, bx);
//                 SWAP(texture_su, texture_eu);
//                 SWAP(texture_sv, texture_ev);
//                 SWAP(texture_sw, texture_ew);
//             }

//             texture_u = texture_su;
//             texture_v = texture_sv;
//             texture_w = texture_sw;

//             float tstep = 1.0f / ((float)(bx - ax));
//             float t = 0.0f;

//             if (ax > WIN_X || bx > WIN_X || ax < 0.0f || bx < 0.0f)
//                 return;
//             for (register int j = ax; j < bx; j++) {
//                 texture_u = (1.0f - t) * texture_su + t * texture_eu;
//                 texture_v = (1.0f - t) * texture_sv + t * texture_ev;
//                 texture_w = (1.0f - t) * texture_sw + t * texture_ew;
//                 int test = WIN_X * i + j;

//                 // printf("Texture Up: %f on %d %d  | %f| %f |\n", texture_w, j, i, texture_u / texture_w, texture_v / texture_w);
//                 if (test > (WIN_X * WIN_Y) || test < 0);
//                 else if (texture_w > engine.DepthBuffer[test]) {
//                     put_pixel(&(engine.depth), j, i, sfImage_getPixel(image, texSize.x * (texture_u / texture_w), texSize.y * (texture_v / texture_w)));
//                     engine.DepthBuffer[test] = texture_w;
//                 }
//                 t += tstep;
//             }

//         }
//     }

//     dy1 = y3 - y2;
//     dx1 = x3 - x2;
//     dv1 = v3 - v2;
//     du1 = u3 - u2;
//     dw1 = w3 - w2;

//     if (dy1) dax_step = dx1 / (float)abs(dy1);
//     if (dy2) dbx_step = dx2 / (float)abs(dy2);

//     du1_step = 0, dv1_step = 0;
//     if (dy1) du1_step = du1 / (float)abs(dy1);
//     if (dy1) dv1_step = dv1 / (float)abs(dy1);
//     if (dy1) dw1_step = dw1 / (float)abs(dy1);

//     if (dy1) {
//         for (register int i = y2; i <= y3; i++) {
//             int ax = x2 + (float)(i - y2) * dax_step;
//             int bx = x1 + (float)(i - y1) * dbx_step;

//             float texture_su = u2 + (float)(i - y2) * du1_step;
//             float texture_sv = v2 + (float)(i - y2) * dv1_step;
//             float texture_sw = w2 + (float)(i - y2) * dw1_step;

//             float texture_eu = u1 + (float)(i - y1) * du2_step;
//             float texture_ev = v1 + (float)(i - y1) * dv2_step;
//             float texture_ew = w1 + (float)(i - y1) * dw2_step;

//             if (ax > bx) {
//                 SWAP(ax, bx);
//                 SWAP(texture_su, texture_eu);
//                 SWAP(texture_sv, texture_ev);
//                 SWAP(texture_sw, texture_ew);
//             }

//             texture_u = texture_su;
//             texture_v = texture_sv;
//             texture_w = texture_sw;

//             float tstep = 1.0f / ((float)(bx - ax));
//             float t = 0.0f;

//             if (ax > WIN_X || bx > WIN_X || ax < 0.0f || bx < 0.0f)
//                 return;
//             for (register int j = ax; j < bx; j++) {
//                 texture_u = (1.0f - t) * texture_su + t * texture_eu;
//                 texture_v = (1.0f - t) * texture_sv + t * texture_ev;
//                 texture_w = (1.0f - t) * texture_sw + t * texture_ew;
//                 int test = WIN_X * i + j;

//                 // printf("Texture Both: %f on %d %d  | %d | %d |\n", texture_w, j, i, (sizint)(texture_u / texture_w), (sizint)(texture_v / texture_w));
//                 if (test > (WIN_X * WIN_Y) || test < 0);
//                 else if (texture_w > engine.DepthBuffer[test]) {
//                     put_pixel(&(engine.depth), j, i, sfImage_getPixel(image, texSize.x * (texture_u / texture_w), texSize.y * (texture_v / texture_w)));
//                     engine.DepthBuffer[test] = texture_w;
//                 }
//                 t += tstep;
//             }
//         }
//     }
// }

static sfVertexArray *create_triangle(triangle_t *node)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1, vertex2, vertex3;

    int lighting = (int)(node->dp * 255);

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
