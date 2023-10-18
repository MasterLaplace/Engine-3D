/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** math_vector
*/

#ifndef MATH_VECTOR_H_
    #define MATH_VECTOR_H_

////////////////////////////////////////////////////////////
// Include the other headers of the math module
////////////////////////////////////////////////////////////
#include "config.h"

////////////////////////////////////////////////////////////
// Include necessary headers for the vector module
////////////////////////////////////////////////////////////
#include <math.h>

////////////////////////////////////////////////////////////
// Define the default vector4 of floats
////////////////////////////////////////////////////////////
#define VECTOR4F_DEFAULT (vector4f){0, 0, 0, 0}
#define VECTOR4F_INIT(x, y, z, w) (vector4f){x, y, z, w}

/**
 * @brief  Structure containing a 4D vector of floats
 *
 * @param x {float} - The x component of the vector
 * @param y {float} - The y component of the vector
 * @param z {float} - The z component of the vector
 * @param w {float} - The w component of the vector
 */
typedef struct {
    float x, y, z, w;
} vector4f;

/**
 * @brief  Addition of two vector4 of floats
 *
 * @param v {vector4f} - The first vector4 of floats
 * @param w {vector4f} - The second vector4 of floats
 * @return {vector4f} - The result of the addition
 */
extern vector4f vector4_f_add(vector4f v, vector4f w);

/**
 * @brief  Substraction of two vector4 of floats
 *
 * @param v {vector4f} - The first vector4 of floats
 * @param w {vector4f} - The second vector4 of floats
 * @return {vector4f} - The result of the substraction
 */
extern vector4f vector4_f_sub(vector4f v, vector4f w);

/**
 * @brief  Multiplication of a vector4 of floats and a float
 *
 * @param v {vector4f} - The vector4 of floats
 * @param w {float} - The float
 * @return {vector4f} - The result of the multiplication
 */
extern vector4f vector4_f_mul(vector4f v, float w);

/**
 * @brief  Division of a vector4 of floats and a float
 *
 * @param v {vector4f} - The vector4 of floats
 * @param w {float} - The float
 * @return {vector4f} - The result of the division
 */
extern vector4f vector4_f_div(vector4f v, float w);


/**
 * @brief  Normalise a vector4 of floats (make its length equal to 1)
 *
 * @param v {vector4f} - The vector4 of floats
 * @return vector4f - The result of the normalisation
 */
extern vector4f vector4_f_normalise(vector4f v);

/**
 * @brief  Compute the cross product of two vector4 of floats
 *
 * @param a {vector4f} - The first vector4 of floats
 * @param b {vector4f} - The second vector4 of floats
 * @return {vector4f} - The result of the cross product
 */
extern vector4f vector4_f_cross_product(vector4f a, vector4f b);

/**
 * @brief  Compute the dot product of two vector4 of floats
 *
 * @param v {vector4f} - The first vector4 of floats
 * @param w {vector4f} - The second vector4 of floats
 * @return {float} - The result of the dot product
 */
extern float vector4_f_dot_product(vector4f v, vector4f w);

/**
 * @brief  Compute the length of a vector4 of floats
 *
 * @param v {vector4f} - The vector4 of floats
 * @return {float} - The length of the vector4 of floats
 */
extern float vector4_f_length(vector4f v);


/**
 * @brief  Compute the intersection of a plane and a line
 *
 * @param plane_p {vector4f} - The point of the plane
 * @param plane_n {vector4f} - The normal of the plane
 * @param line_start {vector4f} - The start of the line
 * @param line_end {vector4f} - The end of the line
 * @return {vector4f} - The intersection of the plane and the line
 */
extern vector4f vector4_f_intersect_plane(vector4f plane_p, vector4f plane_n, vector4f line_start, vector4f line_end);

/**
 * @brief  Compute the intersection of a plane and a line
 *
 * @param plane_p {vector4f} - The point of the plane
 * @param plane_n {vector4f} - The normal of the plane
 * @param line_start {vector4f} - The start of the line
 * @param line_end {vector4f} - The end of the line
 * @param t {float *} - The intersection of the plane and the line
 * @return {vector4f} - The intersection of the plane and the line
 */
extern vector4f vector4_f_intersect_line(vector4f plane_p, vector4f plane_n, vector4f line_start, vector4f line_end, float *t);


/**
 * @brief  Print a vector4 of floats in the console
 *
 * @param v {vector4f} - The vector4 of floats
 */
extern void vector4_f_print(vector4f v);

////////////////////////////////////////////////////////////
// Define the default vector3 of floats
////////////////////////////////////////////////////////////
#define VECTOR3F_DEFAULT (vector3f){0, 0, 0}
#define VECTOR3F_INIT(x, y, z) (vector3f){x, y, z}

/**
 * @brief  Structure containing a 3D vector of floats
 *
 * @param x {float} - The x component of the vector
 * @param y {float} - The y component of the vector
 * @param z {float} - The z component of the vector
 */
typedef struct {
    float x, y, z;
} vector3f;

/**
 * @brief  Addition of two vector3 of floats
 *
 * @param v {vector3f} - The first vector3 of floats
 * @param w {vector3f} - The second vector3 of floats
 * @return {vector3f} - The result of the addition
 */
extern vector3f vector3_f_add(vector3f v, vector3f w);

/**
 * @brief  Substraction of two vector3 of floats
 *
 * @param v {vector3f} - The first vector3 of floats
 * @param w {vector3f} - The second vector3 of floats
 * @return {vector3f} - The result of the substraction
 */
extern vector3f vector3_f_sub(vector3f v, vector3f w);

/**
 * @brief  Multiplication of a vector3 of floats and a float
 *
 * @param v {vector3f} - The vector3 of floats
 * @param w {float} - The float
 * @return {vector3f} - The result of the multiplication
 */
extern vector3f vector3_f_mul(vector3f v, float w);

/**
 * @brief  Division of a vector3 of floats and a float
 *
 * @param v {vector3f} - The vector3 of floats
 * @param w {float} - The float
 * @return {vector3f} - The result of the division
 */
extern vector3f vector3_f_div(vector3f v, float w);


/**
 * @brief  Normalise a vector3 of floats (make its length equal to 1)
 *
 * @param v {vector3f} - The vector3 of floats
 * @return vector3f - The result of the normalisation
 */
extern vector3f vector3_f_normalise(vector3f v);

/**
 * @brief  Compute the cross product of two vector3 of floats
 *
 * @param a {vector3f} - The first vector3 of floats
 * @param b {vector3f} - The second vector3 of floats
 * @return {vector3f} - The result of the cross product
 */
extern vector3f vector3_f_cross_product(vector3f a, vector3f b);

/**
 * @brief  Compute the dot product of two vector3 of floats
 *
 * @param v {vector3f} - The first vector3 of floats
 * @param w {vector3f} - The second vector3 of floats
 * @return {float} - The result of the dot product
 */
extern float vector3_f_dot_product(vector3f v, vector3f w);

/**
 * @brief  Compute the length of a vector3 of floats
 *
 * @param v {vector3f} - The vector3 of floats
 * @return {float} - The length of the vector3 of floats
 */
extern float vector3_f_length(vector3f v);


/**
 * @brief  Compute the intersection of a plane and a line
 *
 * @param plane_p {vector3f} - The point of the plane
 * @param plane_n {vector3f} - The normal of the plane
 * @param line_start {vector3f} - The start of the line
 * @param line_end {vector3f} - The end of the line
 * @return {vector3f} - The intersection of the plane and the line
 */
extern vector3f vector3_f_intersect_plane(vector3f plane_p, vector3f plane_n, vector3f line_start, vector3f line_end);

/**
 * @brief  Compute the intersection of a plane and a line
 *
 * @param plane_p {vector3f} - The point of the plane
 * @param plane_n {vector3f} - The normal of the plane
 * @param line_start {vector3f} - The start of the line
 * @param line_end {vector3f} - The end of the line
 * @param t {float *} - The intersection of the plane and the line
 * @return {vector3f} - The intersection of the plane and the line
 */
extern vector3f vector3_f_intersect_line(vector3f plane_p, vector3f plane_n, vector3f line_start, vector3f line_end, float *t);


/**
 * @brief  Print a vector3 of floats in the console
 *
 * @param v {vector3f} - The vector3 of floats
 */
extern void vector3_f_print(vector3f v);

#endif /* !MATH_VECTOR_H_ */
