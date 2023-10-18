/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** matrix
*/

#include "math_matrix.h"
#include <stdio.h>

matrix4f matrix4_f_mul(matrix4f m, matrix4f n)
{
    matrix4f o = MATRIX4F_DEFAULT;

    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            for (unsigned k = 0; k < 4; k++)
                o.m[i][j] += m.m[i][k] * n.m[k][j];

    return o;
}

vector4f matrix4_f_mul_vector4_f(matrix4f m, vector4f v)
{
    vector4f o = VECTOR4F_DEFAULT;

    o.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + v.w * m.m[3][0];
    o.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + v.w * m.m[3][1];
    o.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + v.w * m.m[3][2];
    o.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];

    return o;
}

vector3f matrix4_f_mul_vector3_f(matrix4f m, vector3f v)
{
    vector3f o = VECTOR3F_DEFAULT;

    o.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];
    o.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];
    o.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];

    return o;
}

matrix4f matrix4_f_quick_inverse(matrix4f m)
{
    matrix4f o = MATRIX4F_DEFAULT;

    memcpy(o.m, m.m, sizeof(float) * 16);

    o.m[3][0] = -(m.m[3][0] * o.m[0][0] + m.m[3][1] * o.m[1][0] + m.m[3][2] * o.m[2][0]);
    o.m[3][1] = -(m.m[3][0] * o.m[0][1] + m.m[3][1] * o.m[1][1] + m.m[3][2] * o.m[2][1]);
    o.m[3][2] = -(m.m[3][0] * o.m[0][2] + m.m[3][1] * o.m[1][2] + m.m[3][2] * o.m[2][2]);
    o.m[0][3] = o.m[1][3] = o.m[2][3] = 0.0f;
    o.m[3][3] = 1.0f;

    return o;
}

void matrix4_f_print(matrix4f m)
{
    printf("[matrix4f]:\n");
    printf("\t%f %f %f %f\n", m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3]);
    printf("\t%f %f %f %f\n", m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3]);
    printf("\t%f %f %f %f\n", m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3]);
    printf("\t%f %f %f %f\n", m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]);
}
