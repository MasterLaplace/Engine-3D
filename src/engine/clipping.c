/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** clipping
*/

#include "engine.h"

int Triangle_ClipAgainstPlane(sfVector4f front, sfVector4f back, triangle_t *intri, triangle_t (*outtri)[2])
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

        // Scale to Screen (S2S)
        Scale_in_Screen(&triProjected);

        add_in_FinalMesh(&triProjected);
    }
}
