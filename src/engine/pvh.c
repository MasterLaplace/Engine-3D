/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** Puddle View hierarchy
*/

#include "engine.h"

void apply_force(particule_t *particule, sfVector3f force) {
    particule->accel.x += force.x;
    particule->accel.y += force.y;
    particule->accel.z += force.z;
}

void update_particule(particule_t *particule) {
    particule->speed.x += particule->accel.x;
    particule->speed.y += particule->accel.y;
    particule->speed.z += particule->accel.z;
    particule->pos.x += particule->speed.x;
    particule->pos.y += particule->speed.y;
    particule->pos.z += particule->speed.z;
    particule->accel = (sfVector3f){0, 0, 0};
}

particule_t *create_particule(sfVector3f pos, sfVector3f speed,
    sfVector3f accel)
{
    particule_t *particule = malloc(sizeof(particule_t));

    particule->pos = pos;
    particule->speed = speed;
    particule->accel = accel;
    particule->update = &update_particule;
    return (particule);
}

void draw_particule(sfRenderWindow *window, particule_t *particule)
{
    sfCircleShape *circle = sfCircleShape_create();
    sfVector2f pos = {particule->pos.x, particule->pos.y};

    if (!circle)
        return;
    sfCircleShape_setPosition(circle, pos);
    sfCircleShape_setRadius(circle, 1);
    sfRenderWindow_drawCircleShape(window, circle, NULL);
    sfCircleShape_destroy(circle);
}

void draw_particules(sfRenderWindow *window, link_t *lParticule)
{
    link_t *actual = lParticule;

    if (!actual)
        return;
    do {
        draw_particule(window, (particule_t *)actual->obj);
        actual = actual->next;
    } while (actual != lParticule && actual);
}
