/*
** ME PROJECT, 2022
** DEN-GINER-Master-Laplace
** File description:
** constants
*/

#ifndef CONSTANTS_H_
    #define CONSTANTS_H_
    #define UNUSED __attribute__((unused))
    #define CLEAR "\033[H\033[J"
    #define FRAMERATE 60.0
    #define PI 3.14159f
    #define WINDOW_SIZE 1920, 1080
    #define WIN_Y 1080
    #define WIN_X 1920
    #define RADIAN(degree) (degree * PI / 180.f)
    #define COS(degree) cosf(RADIAN(degree))
    #define SIN(degree) sinf(RADIAN(degree))
    #define ABS(x) (x < 0 ? -x : x)
    #define RAND(min, max) min + (rand() % (max - min))
    #define PERCENT(min, max) ((min * 100) / max)
    #define SWAP(a, b) { typeof(a) tmp = a; a = b; b = tmp; }
    #define KEY_PRESSED sfKeyboard_isKeyPressed
    #define EXIT_84 84
    #define MAP_X 100
    #define MAP_Y 120

typedef unsigned int sizint;

#endif/* !CONSTANTS_H_ */
