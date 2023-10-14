/*
** EPITECH PROJECT, 2023
** Title: Laplace Map Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-14
** File description:
** map_compare
*/

#include "laplace_map.h"

bool laplace_map_cmp_int(void *a, void *b) {
    return *(int *)a == *(int *)b;
}

bool laplace_map_cmp_float(void *a, void *b) {
    return *(float *)a == *(float *)b;
}

bool laplace_map_cmp_double(void *a, void *b) {
    return *(double *)a == *(double *)b;
}

bool laplace_map_cmp_char(void *a, void *b) {
    return *(char *)a == *(char *)b;
}

bool laplace_map_cmp_str(void *a, void *b) {
    return strcmp((char *)a, (char *)b) == 0;
}

bool laplace_map_cmp_ptr(void *a, void *b) {
    return a == b;
}

bool laplace_map_cmp_bool(void *a, void *b) {
    return *(bool *)a == *(bool *)b;
}
