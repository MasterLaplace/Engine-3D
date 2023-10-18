/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** matrix
*/

#ifndef MATRIX_H_
    #define MATRIX_H_

////////////////////////////////////////////////////////////
// Include the other headers of the math module
////////////////////////////////////////////////////////////
#include "math_vector.h"

////////////////////////////////////////////////////////////
// Include necessary headers for the matrix module
////////////////////////////////////////////////////////////
#ifdef __cplusplus
    #include <cstring>

    using namespace std;
    extern "C" {
#else
    #include <string.h>
#endif

////////////////////////////////////////////////////////////
// Define the default matrix4 of floats
////////////////////////////////////////////////////////////
#define MATRIX4F_DEFAULT (matrix4f){{{0}}}

/**
 * @brief  A 4x4 matrix of floats
 *
 * @param m {float[4][4]} - The matrix
 */
typedef struct {
	float m[4][4];
} matrix4f;

/**
 * @brief  Multiply two matrix4 of floats
 *
 * @param m {matrix4f} - The first matrix
 * @param n {matrix4f} - The second matrix
 * @return {matrix4f} - The result matrix
 */
extern matrix4f matrix4_f_mul(matrix4f m, matrix4f n);

/**
 * @brief  Multiply a matrix4 of floats and a vector4 of floats
 *
 * @param m {matrix4f} - The matrix
 * @param v {vector4f} - The vector
 * @return {vector4f} - The result vector
 */
extern vector4f matrix4_f_mul_vector4_f(matrix4f m, vector4f v);

/**
 * @brief Multiply a matrix4 of floats and a vector3 of floats
 *
 * @param m {matrix4f} - The matrix
 * @param v {vector3f} - The vector
 * @return {vector3f} - The result vector
 */
extern vector3f matrix4_f_mul_vector3_f(matrix4f m, vector3f v);

/**
 * @brief  Get the quick inverse of a matrix4 of floats
 *
 * @param m {matrix4f} - The matrix
 * @return {matrix4f} - The result matrix
 */
extern matrix4f matrix4_f_quick_inverse(matrix4f m);

/**
 * @brief  Print a matrix4 of floats
 *
 * @param m {matrix4f} - The matrix
 */
extern void matrix4_f_print(matrix4f m);

#ifdef __cplusplus
    }
#endif

#endif /* !MATRIX_H_ */
