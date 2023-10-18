/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** point
*/

#include "math_point.h"
#include <stdio.h>

point_f point_f_add(point_f p, point_f w) {
    return (point_f){p.x + w.x, p.y + w.y};
}

point_f point_f_sub(point_f p, point_f w) {
    return (point_f){p.x - w.x, p.y - w.y};
}

point_f point_f_mul(point_f p, float w) {
    return (point_f){p.x * w, p.y * w};
}

point_f point_f_div(point_f p, float w) {
    return (point_f){p.x / w, p.y / w};
}

void point_f_print(point_f p) {
    printf("[point_f]: (%f, %f)\n", p.x, p.y);
}
