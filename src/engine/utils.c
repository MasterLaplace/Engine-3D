/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** utils
*/

#include "engine.h"

sfVector4f_t Vector_Add(sfVector4f_t v, sfVector4f_t w)
{
    return (sfVector4f_t){v.x + w.x, v.y + w.y, v.z + w.z, 1.f};
}

sfVector4f_t Vector_Sub(sfVector4f_t v, sfVector4f_t w)
{
    return (sfVector4f_t){v.x - w.x, v.y - w.y, v.z - w.z, 1.f};
}

sfVector4f_t Vector_Mul(sfVector4f_t v, float w)
{
    return (sfVector4f_t){v.x * w, v.y * w, v.z * w, w};
}

sfVector4f_t Vector_Div(sfVector4f_t v, float w)
{
    return (sfVector4f_t){v.x / w, v.y / w, v.z / w, w};
}

float Vector_DotProduct(sfVector4f_t v, sfVector4f_t w)
{
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

float Vector_Length(sfVector4f_t v)
{
    return sqrtf(Vector_DotProduct(v, v));
}

float calcul_dist(sfVector4f_t p, sfVector4f_t plane_p, sfVector4f_t plane_n)
{
	return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - Vector_DotProduct(plane_n, plane_p));
}

sfVector4f_t Vector_Normalise(sfVector4f_t v)
{
    float l = Vector_Length(v);
    return (sfVector4f_t){v.x / l, v.y / l, v.z / l, 1.f};
}

sfVector4f_t Vector_CrossProduct(sfVector4f_t a, sfVector4f_t b)
{
    sfVector4f_t l;

    l.x = a.y * b.z - a.z * b.y;
    l.y = a.z * b.x - a.x * b.z;
    l.z = a.x * b.y - a.y * b.x;
    return l;
}

sfVector4f_t Matrix_MultiplyVector(sfVector4f_t v, float (*m)[4], sfVector4f_t w)
{
    v.x = w.x * m[0][0] + w.y * m[1][0] + w.z * m[2][0] + w.w * m[3][0];
    v.y = w.x * m[0][1] + w.y * m[1][1] + w.z * m[2][1] + w.w * m[3][1];
    v.z = w.x * m[0][2] + w.y * m[1][2] + w.z * m[2][2] + w.w * m[3][2];
    v.w = w.x * m[0][3] + w.y * m[1][3] + w.z * m[2][3] + w.w * m[3][3];
    return v;
}

sfVector4f_t Vector_intersectPlane(sfVector4f_t plane_p, sfVector4f_t plane_n, sfVector4f_t lineStart, sfVector4f_t lineEnd)
{
    plane_n = Vector_Normalise(plane_n);
    float plane_d = -Vector_DotProduct(plane_n, plane_p);
    float ad = Vector_DotProduct(lineStart, plane_n);
    float t = (-plane_d - ad) / (Vector_DotProduct(lineEnd, plane_n) - ad);
    return Vector_Add(lineStart, Vector_Mul(Vector_Sub(lineEnd, lineStart), t));
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

void Matrix_QuickInverse(float (*m)[4])
{
    m[0][0] = m[0][0]; m[0][1] = m[1][0]; m[0][2] = m[2][0]; m[0][3] = 0.0f;
    m[1][0] = m[0][1]; m[1][1] = m[1][1]; m[1][2] = m[2][1]; m[1][3] = 0.0f;
    m[2][0] = m[0][2]; m[2][1] = m[1][2]; m[2][2] = m[2][2]; m[2][3] = 0.0f;
    m[3][0] = -(m[3][0] * m[0][0] + m[3][1] * m[1][0] + m[3][2] * m[2][0]);
    m[3][1] = -(m[3][0] * m[0][1] + m[3][1] * m[1][1] + m[3][2] * m[2][1]);
    m[3][2] = -(m[3][0] * m[0][2] + m[3][1] * m[1][2] + m[3][2] * m[2][2]);
    m[3][3] = 1.0f;
}
