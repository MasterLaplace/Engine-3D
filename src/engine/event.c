/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** event
*/

#include "engine.h"

void manage_move()
{
    float velocity = 1.0f;

    if (KEY_PRESSED(sfKeyLControl))
        velocity = 2.f;

    sfVector4f_t Forward = Vector_Mul(engine.Dir, velocity);

    if (KEY_PRESSED(sfKeyZ))
        engine.Pos = Vector_Add(engine.Pos, Forward);
    if (KEY_PRESSED(sfKeyS))
        engine.Pos = Vector_Sub(engine.Pos, Forward);
}

void analyse_events(sfEvent event)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(WINDOW);
    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyEscape)
            sfRenderWindow_close(WINDOW);
    }
}
