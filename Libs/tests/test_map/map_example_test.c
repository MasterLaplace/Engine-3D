/*
** EPITECH PROJECT, 2023
** Title: Laplace Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-14
** File description:
** map_example_test
*/

#include <criterion/criterion.h>

#include "laplace_map.h"

#define NB_WAVE 10

typedef struct wave_s {
    double wave_length;
    double wave_speed;
    double wave_direction;
} wave_t;

map_t *wave_list;

// When you want to add an element to the list, you do this:
void init_wave()
{
    wave_list = NULL;

    for (unsigned i = 0; i < NB_WAVE; i++) {
        wave_t *wave = malloc(sizeof(wave_t));
        wave->wave_length = 0;
        wave->wave_speed = 0;
        wave->wave_direction = 0;

        int *key = malloc(sizeof(int));
        *key = (int)i;

        // Add the wave as obj in the map list with the key
        laplace_map_append(&(wave_list), laplace_map_create(key, wave));
    }
}

void free_wave(map_t *map)
{
    int *key = (int *)map->key;
    wave_t *wave = (wave_t *)map->obj;

    // Free the key
    free(key);
    // Free the wave and all its content
    free((wave_t *)wave);
}

// When you want to delete all elements from the list, you do this:
void delete_all_wave()
{
    if (!wave_list)
        return;
    while (wave_list) {
        laplace_map_remove(&(wave_list), wave_list, &free_wave);
    }
}

// When you want to loop on the list, you do this:
void print_wave()
{
    map_t *actual = wave_list;

    if (!actual)
        return;
    do {
        wave_t *wave = (wave_t *)actual->obj;

        printf("Key: %d\n", *(int *)actual->key);
        printf("wave->wave_length: %f\n", wave->wave_length);
        printf("wave->wave_speed: %f\n", wave->wave_speed);
        printf("wave->wave_direction: %f\n", wave->wave_direction);

        actual = actual->next;
    } while (wave_list && actual != wave_list);
}

Test(map_example, should_not_fail) {
    init_wave();
    print_wave();
    delete_all_wave();
    print_wave();
}
