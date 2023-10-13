/*
** ME PROJECT, 2022
** DEN-GINER-Master-Laplace
** File description:
** wave
*/

#include "engine.h"

/**
 * Calculates the altitude of the wave at a point (x, y) at a time t.
 *
 * @param x (float): x coordinate of the point.
 * @param y (float): Y coordinate of the point.
 * @param t (float): Time instant.
 * @param wave: wave information
 *
 * @return float: Altitude of the wave in (x, y) at time t.
 */
inline static float gerstner_wave(float x, float y, float t, wave_t *wave)
{
    return wave->A * cos(wave->k * (x * cos(wave->wave_direction) + y * sin(wave->wave_direction)) - wave->omega * t);
}

void superpose_waves(link_t *list)
{
    link_t *actual_wave = engine.wave_list;
    link_t *actual = list;
    wave_t *wave = NULL;
    triangle_t *triangle = NULL;

    if (!actual_wave)
        return;
    do {
        wave = (wave_t *) actual_wave->obj;
        if (!wave)
            return; // TODO: average waves points on map point
        do {
            triangle = (triangle_t *) actual->obj;
            triangle->sommet[0].y += gerstner_wave(triangle->sommet[0].x, triangle->sommet[0].z, engine.t, wave);
            triangle->sommet[1].y += gerstner_wave(triangle->sommet[1].x, triangle->sommet[1].z, engine.t, wave);
            triangle->sommet[2].y += gerstner_wave(triangle->sommet[2].x, triangle->sommet[2].z, engine.t, wave);
            actual = actual->next;
        } while (list && actual != list);
        actual_wave = actual_wave->next;
    } while (engine.wave_list && actual_wave != engine.wave_list);
}

static wave_t *create_wave(float A, float wavelength, float wave_speed, float wave_dir)
{
    wave_t *wave = malloc(sizeof(wave_t));
    wave->A = A;
    wave->wavelength = wavelength;
    wave->wave_speed = wave_speed;
    wave->wave_direction = wave_dir;
    wave->k = 2 * PI / wave->wavelength;
    wave->omega = wave->k * wave->wave_speed;
    return wave;
}

static const sizint NB_WAVE = 2;
static const wave_t INFO[] = {
    {.A = 0.05, .wavelength = 20.0, .wave_speed = 5.0, .wave_direction = PI / 2},
    {.A = 0.05, .wavelength = 15.0, .wave_speed = 4.0, .wave_direction = PI / 6},
    {.A = 0.05, .wavelength = 10.0, .wave_speed = 3.0, .wave_direction = PI / 3},
    {.A = 0.05, .wavelength = 20.0, .wave_speed = 2.0, .wave_direction = PI / 0.5},
    {.A = 0.05, .wavelength = 15.0, .wave_speed = 5.0, .wave_direction = PI / 4},
    {.A = 0.05, .wavelength = 10.0, .wave_speed = 2.0, .wave_direction = PI / 5},
    {.A = 0.05, .wavelength = 20.0, .wave_speed = 3.0, .wave_direction = PI / 8}
};

void init_wave()
{
    engine.wave_list = NULL;
    engine.t = 0.0;

    for (sizint i = 0; i < NB_WAVE; i++) {
        wave_t *wave = create_wave(INFO[i].A, INFO[i].wavelength, INFO[i].wave_speed, INFO[i].wave_direction);

        list_append(&(engine.wave_list), create_link(wave));
    }
}

void create_water(sizint Xmax, sizint Ymax)
{
    mesh_t *mesh = malloc(sizeof(mesh_t));
    triangle_t *tri, *tri2 = NULL;
    mesh->lTriangle = NULL; mesh->nb_triangles = 0; mesh->type = WAVE;

    for (sizint i = 0; i < Ymax; i++) {
        for (sizint j = 0; j < Xmax; j++) {
            tri = malloc(sizeof(triangle_t));
            tri->sommet[0] = (sfVector4f){j + 1, 0, i + 1, 1};
            tri->sommet[1] = (sfVector4f){j + 1, 0, i, 1};
            tri->sommet[2] = (sfVector4f){j, 0, i, 1};
            tri->texture[0] = (sfVector3f){35, 35, 1};
            tri->texture[1] = (sfVector3f){35, 0, 1};
            tri->texture[2] = (sfVector3f){0, 0, 1};
            tri->usemtl = WATER;
            list_append(&(mesh->lTriangle), create_link(tri));
            mesh->nb_triangles++;

            tri2 = malloc(sizeof(triangle_t));
            tri2->sommet[0] = (sfVector4f){j, 0, i, 1};
            tri2->sommet[1] = (sfVector4f){j, 0, i + 1, 1};
            tri2->sommet[2] = (sfVector4f){j + 1, 0, i + 1, 1};
            tri2->texture[0] = (sfVector3f){0, 0, 1};
            tri2->texture[1] = (sfVector3f){0, 35, 1};
            tri2->texture[2] = (sfVector3f){35, 35, 1};
            tri2->usemtl = WATER;
            list_append(&(mesh->lTriangle), create_link(tri2));
        }
    }
    list_append(&(LIST_OBJS), create_link(mesh));
}
