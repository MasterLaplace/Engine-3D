/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** clipping
*/

#include "engine.h"

static int Triangle_ClipAgainstPlane(sfVector4f front, sfVector4f back, triangle_t *intri, triangle_t (*outtri)[2])
{
    back = Vector_Normalise(back);

    float d0 = calcul_dist(intri->sommet[0], front, back);
    float d1 = calcul_dist(intri->sommet[1], front, back);
    float d2 = calcul_dist(intri->sommet[2], front, back);

    sfVector4f inside_point[3]; int nInsidePointCount = 0;
    sfVector4f outside_point[3]; int nOutsidePointCount = 0;
    sfVector3f inside_texture[3]; int nInsideTextureCount = 0;
    sfVector3f outside_texture[3]; int nOutsideTextureCount = 0;

    if (d0 >= 0) { inside_point[nInsidePointCount++] = intri->sommet[0];
        inside_texture[nInsideTextureCount++] = intri->texture[0]; }
    else { outside_point[nOutsidePointCount++] = intri->sommet[0];
        outside_texture[nOutsideTextureCount++] = intri->texture[0]; }

    if (d1 >= 0) { inside_point[nInsidePointCount++] = intri->sommet[1];
        inside_texture[nInsideTextureCount++] = intri->texture[1]; }
    else { outside_point[nOutsidePointCount++] = intri->sommet[1];
        outside_texture[nOutsideTextureCount++] = intri->texture[1]; }

    if (d2 >= 0) { inside_point[nInsidePointCount++] = intri->sommet[2];
        inside_texture[nInsideTextureCount++] = intri->texture[2]; }
    else { outside_point[nOutsidePointCount++] = intri->sommet[2];
        outside_texture[nOutsideTextureCount++] = intri->texture[2]; }


    if (!nInsidePointCount) {
        return (0);
    }
    if (nInsidePointCount == 3) {
        memcpy(outtri[0], intri, sizeof(*intri));
        return (1);
    }
    if (nInsidePointCount == 1 && nOutsidePointCount == 2) {
        (*outtri)[0].dp = intri->dp;
        (*outtri)[0].usemtl = intri->usemtl;
        (*outtri)[0].sommet[0] = inside_point[0];
        (*outtri)[0].texture[0] = inside_texture[0];

        float t;
        (*outtri)[0].sommet[1] = Vector_intersectPlane(front, back, inside_point[0], outside_point[0], &t);
        (*outtri)[0].texture[1].x = t * (outside_texture[0].x - inside_texture[0].x) + inside_texture[0].x;
        (*outtri)[0].texture[1].y = t * (outside_texture[0].y - inside_texture[0].y) + inside_texture[0].y;
        (*outtri)[0].texture[1].z = t * (outside_texture[0].z - inside_texture[0].z) + inside_texture[0].z;

        (*outtri)[0].sommet[2] = Vector_intersectPlane(front, back, inside_point[0], outside_point[1], &t);
        (*outtri)[0].texture[2].x = t * (outside_texture[1].x - inside_texture[0].x) + inside_texture[0].x;
        (*outtri)[0].texture[2].y = t * (outside_texture[1].y - inside_texture[0].y) + inside_texture[0].y;
        (*outtri)[0].texture[2].z = t * (outside_texture[1].z - inside_texture[0].z) + inside_texture[0].z;
        return (1);
    }
    if (nInsidePointCount == 2 && nOutsidePointCount == 1) {
        float t;

        (*outtri)[0].dp = intri->dp;
        (*outtri)[0].usemtl = intri->usemtl;
        (*outtri)[0].sommet[0] = inside_point[0]; (*outtri)[0].texture[0] = inside_texture[0];
        (*outtri)[0].sommet[1] = inside_point[1]; (*outtri)[0].texture[1] = inside_texture[1];

        (*outtri)[0].sommet[2] = Vector_intersectPlane(front, back, inside_point[0], outside_point[0], &t);
        (*outtri)[0].texture[2].x = t * (outside_texture[0].x - inside_texture[0].x) + inside_texture[0].x;
        (*outtri)[0].texture[2].y = t * (outside_texture[0].y - inside_texture[0].y) + inside_texture[0].y;
        (*outtri)[0].texture[2].z = t * (outside_texture[0].z - inside_texture[0].y) + inside_texture[0].z;

        (*outtri)[1].dp = intri->dp;
        (*outtri)[1].usemtl = intri->usemtl;
        (*outtri)[1].sommet[0] = inside_point[1]; (*outtri)[1].texture[0] = inside_texture[1];
        (*outtri)[1].sommet[1] = (*outtri)[0].sommet[2]; (*outtri)[1].texture[1] = (*outtri)[0].texture[2];

        (*outtri)[1].sommet[2] = Vector_intersectPlane(front, back, inside_point[1], outside_point[0], &t);
        (*outtri)[1].texture[2].x = t * (outside_texture[0].x -inside_texture[1].x) + inside_texture[1].x;
        (*outtri)[1].texture[2].y = t * (outside_texture[0].y -inside_texture[1].y) + inside_texture[1].y;
        (*outtri)[1].texture[2].z = t * (outside_texture[0].z - inside_texture[1].y) + inside_texture[1].z;
        return (2);
    }
    return (-1);
}

void clipping(triangle_t triangle)
{
    int nClippedTriangle = 0;
    triangle_t triProjected;
    triangle_t Clipped[2];

    if ((nClippedTriangle = Triangle_ClipAgainstPlane(
            (sfVector4f){0.0f, 0.0f, 0.1f, 1.f},
            (sfVector4f){0.0f, 0.0f, 1.0f, 1.f},
            &triangle, &Clipped
        )) == -1) return;

    for (sizint i = 0; i < (sizint) nClippedTriangle; i++) {
        //* View to Projection (V2P) */
        triProjected.sommet[0] = Matrix_MultiplyVector(triProjected.sommet[0], engine.ViewtoProjection, Clipped[i].sommet[0]);
        triProjected.sommet[1] = Matrix_MultiplyVector(triProjected.sommet[1], engine.ViewtoProjection, Clipped[i].sommet[1]);
        triProjected.sommet[2] = Matrix_MultiplyVector(triProjected.sommet[2], engine.ViewtoProjection, Clipped[i].sommet[2]);
        triProjected.texture[0] = Clipped[i].texture[0];
        triProjected.texture[1] = Clipped[i].texture[1];
        triProjected.texture[2] = Clipped[i].texture[2];
        triProjected.usemtl = Clipped[i].usemtl;
        triProjected.dp = Clipped[i].dp;

        triProjected.texture[0].x = triProjected.texture[0].x / triProjected.texture[0].z;
        triProjected.texture[1].x = triProjected.texture[1].x / triProjected.texture[1].z;
        triProjected.texture[2].x = triProjected.texture[2].x / triProjected.texture[2].z;

        triProjected.texture[0].y = triProjected.texture[0].y / triProjected.texture[0].z;
        triProjected.texture[1].y = triProjected.texture[1].y / triProjected.texture[1].z;
        triProjected.texture[2].y = triProjected.texture[2].y / triProjected.texture[2].z;

        triProjected.texture[0].z = 1.f / triProjected.texture[0].z;
        triProjected.texture[1].z = 1.f / triProjected.texture[1].z;
        triProjected.texture[2].z = 1.f / triProjected.texture[2].z;

        // Scale to Screen (S2S)
        Scale_in_Screen(&triProjected);

        add_in_FinalMesh(&triProjected);
    }
}

// static void draw_triangles(link_t *mesh)
// {
//     link_t *actual = mesh;
//     triangle_t *node = NULL;

//     if (!actual)
//         return;
//     do {
//         node = (triangle_t *) actual->obj;
//         TexturedTriangle((triangle_t *) actual->obj,
//             engine.images[node->usemtl], sfTexture_getSize(engine.textures[node->usemtl]->texture));
//         actual = actual->next;
//     } while (mesh && actual->next != mesh);
// }

// void chek_FinalMesh() {
//     triangle_t *triToRaster = NULL;

//     // Loop through all transformed, viewed, projected, and sorted triangles
//     if (!engine.FinalMesh)
//         return;
//     while (engine.FinalMesh) {
//         triToRaster = (triangle_t *) engine.FinalMesh->obj;
//         triangle_t Clipped[2];
//         link_t *listTriangles = NULL;

//         // Add initial triangle
//         list_append(&listTriangles, create_link(triToRaster));
//         int nNewTriangles = 1;

//         for (sizint p = 0; p < 4; p++) {
//             int nTrisToAdd = 0;
//             while (nNewTriangles > 0) {
//                 // Take triangle from front of queue
//                 triangle_t *test = (triangle_t *) listTriangles->obj;
//                 list_remove(&(listTriangles), listTriangles);
//                 nNewTriangles--;

//                 switch (p) {
//                     case 0:
//                         nTrisToAdd = Triangle_ClipAgainstPlane((sfVector4f){ 0.0f, 0.0f, 0.0f, 1 }, (sfVector4f){ 0.0f, 1.0f, 0.0f, 1 }, test, &Clipped);
//                         break;
//                     case 1:
//                         nTrisToAdd = Triangle_ClipAgainstPlane((sfVector4f){ 0.0f, (float)WIN_Y - 1, 0.0f, 1 }, (sfVector4f){ 0.0f, -1.0f, 0.0f , 1}, test, &Clipped);
//                         break;
//                     case 2:
//                         nTrisToAdd = Triangle_ClipAgainstPlane((sfVector4f){ 0.0f, 0.0f, 0.0f, 1 }, (sfVector4f){ 1.0f, 0.0f, 0.0f, 1 }, test, &Clipped);
//                         break;
//                     case 3:
//                         nTrisToAdd = Triangle_ClipAgainstPlane((sfVector4f){ (float)WIN_X - 1, 0.0f, 0.0f, 1 }, (sfVector4f){ -1.0f, 0.0f, 0.0f, 1 }, test, &Clipped);
//                         break;
//                 }
//                 for (int w = 0; w < nTrisToAdd; w++)
//                     list_append(&listTriangles, create_link(&Clipped[w]));
//             }
//             nNewTriangles = len_link(listTriangles);
//         }

//         // Draw the transformed, viewed, clipped, projected, sorted, clipped triangles
//         draw_triangles(listTriangles);
//         // clean_triangles(listTriangles);
//         list_remove(&(engine.FinalMesh), engine.FinalMesh);
//     }
// }
