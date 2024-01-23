/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** event
*/

#include "engine.h"

static bool is_sphere_triangle_collision(sfVector4f sphere_center, float sphere_radius, triangle_t triangle) {
    sfVector4f triangle_normal = Vector_CrossProduct(Vector_Sub(triangle.sommet[1], triangle.sommet[0]), Vector_Sub(triangle.sommet[2], triangle.sommet[0]));
    triangle_normal = Vector_Normalise(triangle_normal);

    float signed_distance = Vector_DotProduct(Vector_Sub(sphere_center, triangle.sommet[0]), triangle_normal);
    if (fabs(signed_distance) > sphere_radius)
        return false;

    for (int i = 0; i < 3; i++) {
        sfVector4f edge_start = triangle.sommet[i];
        sfVector4f edge_end = triangle.sommet[(i + 1) % 3];

        sfVector4f edge_direction = Vector_Sub(edge_end, edge_start);
        float edge_projection = Vector_DotProduct(Vector_Sub(sphere_center, edge_start), edge_direction) / Vector_DotProduct(edge_direction, edge_direction);
        sfVector4f closest_point_on_edge = Vector_Add(edge_start, Vector_Mul(edge_direction, edge_projection));

        if (0 <= edge_projection && edge_projection <= 1 && Vector_Length(Vector_Sub(closest_point_on_edge, sphere_center)) < sphere_radius)
            return true;
    }
    return false;
}

static sfVector4f resolve_sphere_triangle_collision(sfVector4f sphere_center, float sphere_radius, triangle_t triangle) {
    sfVector4f triangle_normal = Vector_CrossProduct(Vector_Sub(triangle.sommet[1], triangle.sommet[0]), Vector_Sub(triangle.sommet[2], triangle.sommet[0]));
    triangle_normal = Vector_Normalise(triangle_normal);

    float signed_distance = Vector_DotProduct(Vector_Sub(sphere_center, triangle.sommet[0]), triangle_normal);

    if (fabs(signed_distance) < sphere_radius) {
        float penetration_depth = sphere_radius - fabs(signed_distance);

        sfVector4f penetration_vector = Vector_Mul(triangle_normal, penetration_depth);

        if (signed_distance < 0) {
            return Vector_Sub(sphere_center, penetration_vector);
        } else {
            return Vector_Add(sphere_center, penetration_vector);
        }
    }
    return sphere_center;
}

#define GRAVITY 9.81 // Acceleration due to gravity (m/s^2)
#define TIME_STEP (1 / FRAMERATE * (FRAMERATE/10)) // Time step for simulation (s)

static void jump()
{
    // Velocity (m/s)
    if (engine.state == JUMP) {
        engine.Pos.y += engine.velocity_y * TIME_STEP + 1 * -GRAVITY * TIME_STEP * TIME_STEP;
        engine.velocity_y += -GRAVITY * TIME_STEP;
    }
}

static void manage_mouse()
{
    static int save_mouseY = 0; static int save_mouseX = 0;
    sfVector2i pos = sfMouse_getPositionRenderWindow(WINDOW);
    static int sensibility = 1;

    if (pos.x >= WIN_X - sensibility)
        sfMouse_setPositionRenderWindow((sfVector2i) {sensibility + 10, pos.y}, WINDOW);
    if (pos.x <= sensibility)
        sfMouse_setPositionRenderWindow((sfVector2i) {WIN_X - sensibility - 10, pos.y}, WINDOW);
    if (pos.y >= WIN_Y - sensibility)
        sfMouse_setPositionRenderWindow((sfVector2i) {pos.x, sensibility + 10}, WINDOW);
    if (pos.y <= sensibility)
        sfMouse_setPositionRenderWindow((sfVector2i) {pos.x, WIN_Y - sensibility - 10}, WINDOW);

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

static void check_collision()
{
    engine.Pos.x = fmax(engine.Pos.x, engine.root->s_g[0].x);
    engine.Pos.y = fmax(engine.Pos.y, engine.root->s_g[0].y);
    engine.Pos.z = fmax(engine.Pos.z, engine.root->s_g[0].z);
    engine.Pos.x = fmin(engine.Pos.x, engine.root->s_g[1].x);
    engine.Pos.y = fmin(engine.Pos.y, engine.root->s_g[1].y);
    engine.Pos.z = fmin(engine.Pos.z, engine.root->s_g[1].z);
}

void manage_move()
{
    static const float speed_min = 0.5f;
    static const float speed_max = 1.5f;
    static const float friction = 0.1f;
    static float speed = 1.0f;

    speed += (KEY_PRESSED(sfKeyLControl))?(speed >= speed_max)?0:friction:(speed <= speed_min)?0:-friction;

    sfVector4f Forward = Vector_Mul(engine.Dir, speed);
    Forward.y = 0;

    if (KEY_PRESSED(sfKeyUp))
        engine.Pos.y += 0.5f;
    if (KEY_PRESSED(sfKeySpace)) {
        engine.state = JUMP;
        engine.velocity_y = 11.f;
    }
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

    // apply gravity
    if (engine.state != JUMP)
        engine.Pos.y += engine.velocity_y * -GRAVITY * TIME_STEP * TIME_STEP;
    else
        jump();

    manage_mouse();
    check_collision();

    link_t *actual = engine.list_objs;
    do {
        mesh_t *mesh = (mesh_t *) actual->obj;
        link_t *actual2 = mesh->lTriangle;
        do {
            triangle_t *triangle = (triangle_t *) actual2->obj;
            if (is_sphere_triangle_collision(engine.Pos, engine.radius, *triangle)) {
                // triangle->usemtl = NONE;
                engine.Pos = resolve_sphere_triangle_collision(engine.Pos, engine.radius, *triangle);
                engine.state = IDLE;
                engine.velocity_y = 5.f;
            }
            // else {
            //     triangle->usemtl = HIGH;
            // }
            actual2 = actual2->next;
        } while (mesh->lTriangle && actual2 != mesh->lTriangle);
        actual = actual->next;
    } while (engine.list_objs && actual != engine.list_objs);
}

void analyse_events(sfEvent event)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(WINDOW);
    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyEscape)
            sfRenderWindow_close(WINDOW);
        if (event.key.code == sfKeyP) {
            if (engine.drunkerMode)
                engine.drunkerMode = false;
            else
                engine.drunkerMode = true;
        }
    }
}
