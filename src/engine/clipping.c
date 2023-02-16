/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** clipping
*/

#include "engine.h"

static int Triangle_ClipAgainstPlane(sfVector4f_t front, sfVector4f_t back, triangle_t *intri, triangle_t (*outtri)[2])
{
    back = Vector_Normalise(back);

    float d0 = calcul_dist(intri->sommet[0], front, back);
    float d1 = calcul_dist(intri->sommet[1], front, back);
    float d2 = calcul_dist(intri->sommet[2], front, back);

    sfVector4f_t inside_point[3]; int nInsidePointCount = 0;
    sfVector4f_t outside_point[3]; int nOutsidePointCount = 0;

    if (d0 >= 0) { inside_point[nInsidePointCount++] = intri->sommet[0]; }
    else { outside_point[nOutsidePointCount++] = intri->sommet[0]; }

    if (d1 >= 0) { inside_point[nInsidePointCount++] = intri->sommet[1]; }
    else { outside_point[nOutsidePointCount++] = intri->sommet[1]; }

    if (d2 >= 0) { inside_point[nInsidePointCount++] = intri->sommet[2]; }
    else { outside_point[nOutsidePointCount++] = intri->sommet[2]; }


    if (!nInsidePointCount) {
        return (0);
    }
    if (nInsidePointCount == 3) {
        memcpy(outtri[0], intri, sizeof(*intri));
        return (1);
    }
    if (nInsidePointCount == 1 && nOutsidePointCount == 2) {
        outtri[0]->dp = intri->dp;
        outtri[0]->sommet[0] = inside_point[0];
        outtri[0]->sommet[1] = Vector_intersectPlane(front, back, inside_point[0], outside_point[0]);
        outtri[0]->sommet[2] = Vector_intersectPlane(front, back, inside_point[0], outside_point[1]);
        return (1);
    }
    if (nInsidePointCount == 2 && nOutsidePointCount == 1) {
        outtri[0]->dp = intri->dp;
        outtri[0]->sommet[0] = inside_point[0];
        outtri[0]->sommet[1] = inside_point[1];
        outtri[0]->sommet[2] = Vector_intersectPlane(front, back, inside_point[0], outside_point[0]);

        outtri[1]->dp = intri->dp;
        outtri[1]->sommet[0] = inside_point[1];
        outtri[1]->sommet[1] = outtri[0]->sommet[2];
        outtri[1]->sommet[2] = Vector_intersectPlane(front, back, inside_point[1], outside_point[0]);
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
            (sfVector4f_t){0.0f, 0.0f, 0.1f, 1.f},
            (sfVector4f_t){0.0f, 0.0f, 1.0f, 1.f},
            &triangle, &Clipped
        )) == -1) return;

    for (sizint i = 0; i < (sizint) nClippedTriangle; i++) {
        //* View to Projection (V2P) */
        triProjected.sommet[0] = Matrix_MultiplyVector(triProjected.sommet[0], engine.ViewtoProjection, Clipped[i].sommet[0]);
        triProjected.sommet[1] = Matrix_MultiplyVector(triProjected.sommet[1], engine.ViewtoProjection, Clipped[i].sommet[1]);
        triProjected.sommet[2] = Matrix_MultiplyVector(triProjected.sommet[2], engine.ViewtoProjection, Clipped[i].sommet[2]);
        triProjected.dp = Clipped[i].dp;

        // Scale to Screen (S2S)
        Scale_in_Screen(&triProjected);

        add_in_FinalMesh(&triProjected);
    }
}
