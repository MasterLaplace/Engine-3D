/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** core
*/

#include "engine.h"

engine_t engine;

void init(void) __attribute__((constructor));
void clean(void) __attribute__((destructor));

void init(void)
{
    if (!open_folder( "./assets/obj_examples/" ))
        exit(EXIT_FAILURE);
    /*graphic*/
    display_init();
    engine.clock = sfClock_create();
    /*camera*/
    engine.Pos = (sfVector4f_t){ 0.f, 0.f, 0.f, 1.f};
    engine.Dir = (sfVector4f_t){ 0.f, 0.f, 0.f, 1.f};
    engine.fawZ = 0.f;
    engine.fawY = 0.f;
    engine.fawX = 0.f;
    /*matrix*/
    memset(engine.ModeltoWorld, 0.f, sizeof(engine.ModeltoWorld));
    memset(engine.WorldtoView, 0.f, sizeof(engine.WorldtoView));
    // View to Projection (V2P)
    memset(engine.ViewtoProjection, 0.f, sizeof(engine.ViewtoProjection));
    Matrix_MakeProjection(90.0f, (float) WIN_Y / (float) WIN_X, 0.1f, 1000.0f);
}

void clean(void)
{
    destroying();
}

int main()
{
    loop_engine();
    return EXIT_SUCCESS;
}
