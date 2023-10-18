/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** math_point
*/

#ifndef MATH_POINT_H_
    #define MATH_POINT_H_

////////////////////////////////////////////////////////////
// Include the other headers of the math module
////////////////////////////////////////////////////////////
#include "config.h"

////////////////////////////////////////////////////////////
// Include necessary headers for the point module
////////////////////////////////////////////////////////////
#include <math.h>

////////////////////////////////////////////////////////////
// Define the default point of floats
////////////////////////////////////////////////////////////
#define POINT_F_DEFAULT (point_f){0, 0}
#define POINT_F_INIT(x, y) (point_f){x, y}

/**
 * @brief  Structure containing a 2D point of floats
 *
 * @param x {float} - The x component of the vector
 * @param y {float} - The y component of the vector
 */
typedef struct {
    float x, y;
} point_f;

/**
 * @brief  Addition of two point of floats
 *
 * @param v {point_f} - The first point of floats
 * @param w {point_f} - The second point of floats
 * @return {point_f} - The result of the addition
 */
extern point_f point_f_add(point_f v, point_f w);

/**
 * @brief  Substraction of two point of floats
 *
 * @param v {point_f} - The first point of floats
 * @param w {point_f} - The second point of floats
 * @return {point_f} - The result of the substraction
 */
extern point_f point_f_sub(point_f v, point_f w);

/**
 * @brief  Multiplication of a point of floats and a float
 *
 * @param v {point_f} - The point of floats
 * @param w {float} - The float
 * @return {point_f} - The result of the multiplication
 */
extern point_f point_f_mul(point_f v, float w);

/**
 * @brief  Division of a point of floats and a float
 *
 * @param v {point_f} - The point of floats
 * @param w {float} - The float
 * @return {point_f} - The result of the division
 */
extern point_f point_f_div(point_f v, float w);

/**
 * @brief  Print a point of floats in the console
 *
 * @param v {point_f} - The point of floats
 */
extern void point_f_print(point_f v);

#endif /* !MATH_POINT_H_ */
