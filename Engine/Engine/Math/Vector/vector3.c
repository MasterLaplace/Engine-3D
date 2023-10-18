/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** vector3
*/

#include "math_vector.h"
#include <stdio.h>

vector3f vector3_f_add(vector3f v, vector3f w) {
    return (vector3f){v.x + w.x, v.y + w.y, v.z + w.z};
}

vector3f vector3_f_sub(vector3f v, vector3f w) {
    return (vector3f){v.x - w.x, v.y - w.y, v.z - w.z};
}

vector3f vector3_f_mul(vector3f v, float w) {
    return (vector3f){v.x * w, v.y * w, v.z * w};
}

vector3f vector3_f_div(vector3f v, float w) {
    return (vector3f){v.x / w, v.y / w, v.z / w};
}

vector3f vector3_f_normalise(vector3f v) {
    float length = vector3_f_length(v);
    return (vector3f){v.x / length, v.y / length, v.z / length};
}

vector3f vector3_f_cross_product(vector3f a, vector3f b) {
    return (vector3f){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

float vector3_f_dot_product(vector3f v, vector3f w) {
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

float vector3_f_length(vector3f v) {
    return sqrtf(vector3_f_dot_product(v, v));
}

vector3f vector3_f_intersect_plane(vector3f plane_p, vector3f plane_n, vector3f line_start, vector3f line_end)
{
    plane_n = vector3_f_normalise(plane_n);
    float plane_d = -vector3_f_dot_product(plane_n, plane_p);
    float ad = vector3_f_dot_product(line_start, plane_n);
    float bd = vector3_f_dot_product(line_end, plane_n);
    float t = (-plane_d - ad) / (bd - ad);
    vector3f line_start_to_end = vector3_f_sub(line_end, line_start);
    vector3f line_to_intersect = vector3_f_mul(line_start_to_end, t);
    return vector3_f_add(line_start, line_to_intersect);
}

vector3f vector3_f_intersect_line(vector3f plane_p, vector3f plane_n, vector3f line_start, vector3f line_end, float *t)
{
    plane_n = vector3_f_normalise(plane_n);
    float plane_d = -vector3_f_dot_product(plane_n, plane_p);
    float ad = vector3_f_dot_product(line_start, plane_n);
    float bd = vector3_f_dot_product(line_end, plane_n);
    *t = (-plane_d - ad) / (bd - ad);
    vector3f line_start_to_end = vector3_f_sub(line_end, line_start);
    vector3f line_to_intersect = vector3_f_mul(line_start_to_end, *t);
    return vector3_f_add(line_start, line_to_intersect);
}

void vector3_f_print(vector3f v) {
    printf("[vector3f]: (%f, %f, %f)\n", v.x, v.y, v.z);
}
