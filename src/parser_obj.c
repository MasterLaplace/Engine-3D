/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** parser_obj
*/

#include "engine.h"

mesh_t *create_obj(char **buf)
{
    mesh_t *mesh = malloc(sizeof(mesh_t));

    two_free(buf);
    return mesh;
}
