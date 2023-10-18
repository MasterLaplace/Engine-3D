/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** math_geometry
*/

#ifndef MATH_GEOMETRY_H_
    #define MATH_GEOMETRY_H_

////////////////////////////////////////////////////////////
// Include the other headers of the math module
////////////////////////////////////////////////////////////
#include "math_vector.h"

////////////////////////////////////////////////////////////
// Include the headers of the external libraries
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Include necessary headers for the geometry module
////////////////////////////////////////////////////////////
#ifdef __cplusplus
    #include <cstdlib>
    #include <cstdbool>
#else
    #include <stdlib.h>
    #include <stdbool.h>
#endif

/**
 * @brief  Structure of a triangle with 3 vertices
 *
 * @param vertices Triangle vertices (x, y, z, w)
 * @param textures Texture coordinates of the triangle (x, y, z)
 * @param dp Distance from camera
 */
typedef struct triangle_s {
    vector4f vertices[3];
    vector3f textures[3];
    // texture usemtl;
    float dp;
} triangle_t;

/**
 * @brief  Create a triangle with 3 vertices
 *
 * @param vertices {vector4f[3]} - The vertices of the triangle
 * @param textures {vector3f[3]} - The texture coordinates of the triangle
 * @return {triangle_t *} - The triangle
 */
extern triangle_t *geometry_triangle_create(vector4f vertices[3], vector3f textures[3]/*, texture usemtl*/);

/**
 * @brief  Destroy a triangle
 *
 * @param triangle {triangle_t *} - The triangle to destroy
 */
extern void geometry_triangle_destroy(triangle_t *triangle);

#endif /* !MATH_GEOMETRY_H_ */
