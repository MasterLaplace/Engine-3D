/*
** EPITECH PROJECT, 2023
** Title: Laplace Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** link_example_test
*/

#include <criterion/criterion.h>

#include <stdio.h>
#include <stdlib.h>
#include "laplace_link.h"

#define NB_WAVE 10

typedef struct wave_s {
    double wavelength;
    double wave_speed;
    double wave_direction;
} wave_t;

link_t *wave_list;

// When you want to add an element to the list, you do this:
void init_wave()
{
    wave_list = NULL;

    for (unsigned i = 0; i < NB_WAVE; i++) {
        wave_t *wave = malloc(sizeof(wave_t));
        wave->wavelength = 0;
        wave->wave_speed = 0;
        wave->wave_direction = 0;

        // Add the wave to the list
        laplace_link_append(&(wave_list), laplace_link_create(wave));
    }
}

void free_wave(void *wave)
{
    // Free the wave and all its content
    free((wave_t *)wave);
}

// When you want to delete an element from the list, you do this:
void delete_wave()
{
    link_t *actual = wave_list;

    if (!actual)
        return;
    do {
        wave_t *wave = (wave_t *)actual->obj;

        if (wave->wavelength == 0) {
            laplace_link_remove(&(wave_list), actual, &free_wave);
            break;
        }

        // If you want to delete the last element of the list, you do this:
        laplace_link_remove(&(wave_list), wave_list->prev, &free_wave);
        // If you want to delete the first element of the list, you do this:
        laplace_link_remove(&(wave_list), wave_list, &free_wave);

        actual = actual->next;
    } while (wave_list && actual != wave_list);
}

// When you want to delete all elements from the list, you do this:
void delete_all_wave()
{
    if (!wave_list)
        return;
    while (wave_list) {
        laplace_link_remove(&(wave_list), wave_list, &free_wave);
    }
}

// When you want to loop on the list, you do this:
void print_wave()
{
    link_t *actual = wave_list;

    if (!actual)
        return;
    do {
        wave_t *wave = (wave_t *)actual->obj;

        printf("Wavelength: %f\n", wave->wavelength);
        printf("Wave speed: %f\n", wave->wave_speed);
        printf("Wave direction: %f\n", wave->wave_direction);

        actual = actual->next;
    } while (wave_list && actual != wave_list);
}

Test(link_example, should_be_not_fail) {
    init_wave();
    print_wave();
    delete_wave();
    print_wave();
    delete_all_wave();
    print_wave();
}
