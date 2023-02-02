/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** clean
*/

#include "engine.h"

void clean_mesh()
{
    if (!engine.list_objs)
        return;
    while (engine.list_objs) {
        free((mesh_t *) engine.list_objs->obj);
        list_remove(&(engine.list_objs), engine.list_objs);
    }
}

void destroying()
{
    clean_mesh();
}
