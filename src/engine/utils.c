/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** utils
*/

#include "engine.h"

inline sfVector4f Vector_Add(sfVector4f v, sfVector4f w)
{
    return (sfVector4f){v.x + w.x, v.y + w.y, v.z + w.z, 1.f};
}

inline sfVector4f Vector_Sub(sfVector4f v, sfVector4f w)
{
    return (sfVector4f){v.x - w.x, v.y - w.y, v.z - w.z, 1.f};
}

inline sfVector4f Vector_Mul(sfVector4f v, float w)
{
    return (sfVector4f){v.x * w, v.y * w, v.z * w, w};
}

inline sfVector4f Vector_Div(sfVector4f v, float w)
{
    return (sfVector4f){v.x / w, v.y / w, v.z / w, w};
}

inline float Vector_DotProduct(sfVector4f v, sfVector4f w)
{
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

inline float Vector_Length(sfVector4f v)
{
    return sqrtf(Vector_DotProduct(v, v));
}

inline float calcul_dist(sfVector4f p, sfVector4f plane_p, sfVector4f plane_n)
{
	return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - Vector_DotProduct(plane_n, plane_p));
}

inline sfVector4f Vector_Normalise(sfVector4f v)
{
    float l = Vector_Length(v);
    return (sfVector4f){v.x / l, v.y / l, v.z / l, 1.f};
}

sfVector4f Vector_CrossProduct(sfVector4f a, sfVector4f b)
{
    sfVector4f l;

    l.x = a.y * b.z - a.z * b.y;
    l.y = a.z * b.x - a.x * b.z;
    l.z = a.x * b.y - a.y * b.x;
    return l;
}

sfVector4f Matrix_MultiplyVector(sfVector4f v, float (*m)[4], sfVector4f w)
{
    v.x = w.x * m[0][0] + w.y * m[1][0] + w.z * m[2][0] + w.w * m[3][0];
    v.y = w.x * m[0][1] + w.y * m[1][1] + w.z * m[2][1] + w.w * m[3][1];
    v.z = w.x * m[0][2] + w.y * m[1][2] + w.z * m[2][2] + w.w * m[3][2];
    v.w = w.x * m[0][3] + w.y * m[1][3] + w.z * m[2][3] + w.w * m[3][3];
    return v;
}

sfVector4f Vector_intersectPlane(sfVector4f plane_p, sfVector4f plane_n, sfVector4f lineStart, sfVector4f lineEnd, float *t)
{
    plane_n = Vector_Normalise(plane_n);
    *t = -Vector_DotProduct(plane_n, plane_p);
    float ad = Vector_DotProduct(lineStart, plane_n);
    *t = (-(*t) - ad) / (Vector_DotProduct(lineEnd, plane_n) - ad);
    return Vector_Add(lineStart, Vector_Mul(Vector_Sub(lineEnd, lineStart), *t));
}

void Matrix_Multiply(float (*m)[4], float (*m1)[4], float (*m2)[4])
{
    for(sizint i = 0; i < 4; i++) {
        for (sizint j = 0; j < 4; j++) {
            m[j][i] = m1[j][0] * m2[0][i]
                    + m1[j][1] * m2[1][i]
                    + m1[j][2] * m2[2][i]
                    + m1[j][3] * m2[3][i];
        }
    }
}

matrix Matrix_QuickInverse(float (*m)[4])
{
    matrix inv;

    for(sizint i = 0; i < 3; i++) {
        for(sizint j = 0; j < 3; j++) {
            inv.m[i][j] = m[j][i];
        }
    }

    inv.m[3][0] = -(m[3][0] * inv.m[0][0] + m[3][1] * inv.m[1][0] + m[3][2] * inv.m[2][0]);
    inv.m[3][1] = -(m[3][0] * inv.m[0][1] + m[3][1] * inv.m[1][1] + m[3][2] * inv.m[2][1]);
    inv.m[3][2] = -(m[3][0] * inv.m[0][2] + m[3][1] * inv.m[1][2] + m[3][2] * inv.m[2][2]);

    inv.m[0][3] = inv.m[1][3] = inv.m[2][3] = 0.0;
    inv.m[3][3] = 1.0;

    return inv;
}

sfVector3f average_triangle(triangle_t *t)
{
    float x = (t->sommet[0].x + t->sommet[1].x + t->sommet[2].x) / 3.0f;
    float y = (t->sommet[0].y + t->sommet[1].y + t->sommet[2].y) / 3.0f;
    float z = (t->sommet[0].z + t->sommet[1].z + t->sommet[2].z) / 3.0f;
    return (sfVector3f){x, y, z};
}
