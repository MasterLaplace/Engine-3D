/*
** EPITECH PROJECT, 2023
** Title: Laplace Map Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-14
** File description:
** map_clean_data
*/

#include "laplace_map.h"

void laplace_map_clean_ptr_int(map_t *map) {
    free((int *)map->key);
    free((int *)map->obj);
}

void laplace_map_clean_ptr_float(map_t *map) {
    free((float *)map->key);
    free((float *)map->obj);
}

void laplace_map_clean_ptr_double(map_t *map) {
    free((double *)map->key);
    free((double *)map->obj);
}

void laplace_map_clean_ptr_char(map_t *map) {
    free((char *)map->key);
    free((char *)map->obj);
}

void laplace_map_clean_ptr_str(map_t *map) {
    free((char *)map->key);
    free((char *)map->obj);
}

void laplace_map_clean_ptr(map_t *map) {
    free((void *)map->key);
    free((void *)map->obj);
}
