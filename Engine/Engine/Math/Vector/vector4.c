/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** vector4
*/

#include "math_vector.h"
#include <stdio.h>

vector4f vector4_f_add(vector4f v, vector4f w) {
    return (vector4f){v.x + w.x, v.y + w.y, v.z + w.z, v.w + w.w};
}

vector4f vector4_f_sub(vector4f v, vector4f w) {
    return (vector4f){v.x - w.x, v.y - w.y, v.z - w.z, v.w - w.w};
}

vector4f vector4_f_mul(vector4f v, float w) {
    return (vector4f){v.x * w, v.y * w, v.z * w, v.w * w};
}

vector4f vector4_f_div(vector4f v, float w) {
    return (vector4f){v.x / w, v.y / w, v.z / w, v.w / w};
}

vector4f vector4_f_normalise(vector4f v) {
    float length = vector4_f_length(v);
    return (vector4f){v.x / length, v.y / length, v.z / length, v.w / length};
}

vector4f vector4_f_cross_product(vector4f a, vector4f b) {
    return (vector4f){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
        0
    };
}

float vector4_f_dot_product(vector4f v, vector4f w) {
    return v.x * w.x + v.y * w.y + v.z * w.z + v.w * w.w;
}

float vector4_f_length(vector4f v) {
    return sqrtf(vector4_f_dot_product(v, v));
}

vector4f vector4_f_intersect_plane(vector4f plane_p, vector4f plane_n, vector4f line_start, vector4f line_end)
{
    plane_n = vector4_f_normalise(plane_n);
    float plane_d = -vector4_f_dot_product(plane_n, plane_p);
    float ad = vector4_f_dot_product(line_start, plane_n);
    float bd = vector4_f_dot_product(line_end, plane_n);
    float t = (-plane_d - ad) / (bd - ad);
    vector4f line_start_to_end = vector4_f_sub(line_end, line_start);
    vector4f line_to_intersect = vector4_f_mul(line_start_to_end, t);
    return vector4_f_add(line_start, line_to_intersect);
}

vector4f vector4_f_intersect_line(vector4f plane_p, vector4f plane_n, vector4f line_start, vector4f line_end, float *t)
{
    plane_n = vector4_f_normalise(plane_n);
    float plane_d = -vector4_f_dot_product(plane_n, plane_p);
    float ad = vector4_f_dot_product(line_start, plane_n);
    float bd = vector4_f_dot_product(line_end, plane_n);
    *t = (-plane_d - ad) / (bd - ad);
    vector4f line_start_to_end = vector4_f_sub(line_end, line_start);
    vector4f line_to_intersect = vector4_f_mul(line_start_to_end, *t);
    return vector4_f_add(line_start, line_to_intersect);
}

void vector4_f_print(vector4f v) {
    printf("[vector4f]: (%f, %f, %f, %f)\n", v.x, v.y, v.z, v.w);
}
