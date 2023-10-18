/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** triangle
*/

#include "math_geometry.h"

triangle_t *geometry_triangle_create(vector4f vertices[3], vector3f textures[3]/*, texture usemtl*/)
{
    triangle_t *triangle = malloc(sizeof(triangle_t));

    triangle->vertices[0] = vertices[0];
    triangle->vertices[1] = vertices[1];
    triangle->vertices[2] = vertices[2];
    triangle->textures[0] = textures[0];
    triangle->textures[1] = textures[1];
    triangle->textures[2] = textures[2];
    return triangle;
}
void geometry_triangle_destroy(triangle_t *triangle)
{
    free(triangle);
}
