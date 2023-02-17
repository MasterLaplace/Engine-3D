/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** event
*/

#include "engine.h"

#define GRAVITY 9.81 // Acceleration due to gravity (m/s^2)
#define TIME_STEP (1 / FRAMERATE * 2) // Time step for simulation (s)

void jump()
{
    // Velocity (m/s)
    static double vy = 11.0;
    engine.state = JUMP;

    if (engine.Pos.y >= 0.0) {
        engine.Pos.y += vy * TIME_STEP + 1 * -GRAVITY * TIME_STEP * TIME_STEP;
        vy += -GRAVITY * TIME_STEP;
    } else {
        engine.state = IDLE;
        engine.Pos.y = 0.0;
        vy = 11.0;
    }
}

void manage_mouse()
{
    static int save_mouseY = 0; static int save_mouseX = 0;
    sfVector2i pos = sfMouse_getPositionRenderWindow(WINDOW);
    static int sensibility = 5;

    if (pos.x > save_mouseX + sensibility || pos.x < save_mouseX - sensibility) {
        if (pos.x >= save_mouseX)
            engine.fawY += 0.1f;
        else
            engine.fawY -= 0.1f;
        save_mouseX = pos.x;
    }
    if (pos.y > save_mouseY + sensibility || pos.y < save_mouseY - sensibility) {
        if (pos.y >= save_mouseY)
            engine.fawX -= 0.05f;
        else
            engine.fawX += 0.05f;
        save_mouseY = pos.y;
    }
}

void manage_move()
{
    static const float speed_min = 0.5f;
    static const float speed_max = 1.5f;
    static const float friction = 0.1f;
    static float speed = 1.0f;

    speed += (KEY_PRESSED(sfKeyLControl))?(speed >= speed_max)?0:friction:(speed <= speed_min)?0:-friction;

    sfVector4f_t Forward = Vector_Mul(engine.Dir, speed);

    if (KEY_PRESSED(sfKeyUp))
        engine.Pos.y += 0.5f;
    else if (KEY_PRESSED(sfKeySpace) || engine.state == JUMP)
        jump();
    if (KEY_PRESSED(sfKeyDown))
        engine.Pos.y -= 0.5f;
    if (KEY_PRESSED(sfKeyZ))
        engine.Pos = Vector_Add(engine.Pos, Forward);
    if (KEY_PRESSED(sfKeyS))
        engine.Pos = Vector_Sub(engine.Pos, Forward);
    if (KEY_PRESSED(sfKeyQ))
        engine.fawY -= 0.1f;
    if (KEY_PRESSED(sfKeyD))
        engine.fawY += 0.1f;
    if (KEY_PRESSED(sfKeyR))
        engine.fawX += 0.1f;
    if (KEY_PRESSED(sfKeyF))
        engine.fawX -= 0.1f;
    // manage_mouse();
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
