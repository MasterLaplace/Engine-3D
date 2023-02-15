/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** engine
*/

#ifndef ENGINE_H_
    #define ENGINE_H_
    #define LIST_OBJS engine.list_objs
    #define WINDOW engine.window
    #include <SFML/Graphics.h>
    #include <stdbool.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <math.h>
    #include "linkList.h"
    #include "constants.h"
    #include "my.h"

typedef struct engine_s engine_t;

typedef struct sfVector4f_s {
    float x, y, z, w;
} sfVector4f_t;

typedef struct triangle_s {
    sfVector4f_t sommet[3];
    sfVector3f texture[3];
    float dp;
} triangle_t;

typedef struct mesh_s {
    link_t *lTriangle;
    sizint nb_triangles;
} mesh_t;


struct engine_s {
    /*graphic*/
    sfRenderWindow *window;
    sfClock *clock;
    /*camera*/
    sfVector4f_t Pos;
    sfVector4f_t Dir;
    float fawZ;
    float fawY;
    float fawX;
    /*matrix*/
    float ModeltoWorld[4][4];
    float WorldtoView[4][4];
    float ViewtoProjection[4][4];
    /*link*/
    link_t *list_objs;
    link_t *FinalMesh;
};

extern engine_t engine;

/* INIT */
bool open_folder(char *path);
void display_init();

/* CLEAN */
void clean_triangles(link_t *mesh);
void destroying();

/* PARSER OBJ */
mesh_t *create_obj(char **buf);

/* LOOP */
void loop_engine();

/* EVENT */
void analyse_events(sfEvent event);
void manage_move();

/* RASTERIZEING */
void vectors_3d_to_2d();
void Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
sfVector4f_t Matrix_MultiplyVector(sfVector4f_t v, float (*m)[4], sfVector4f_t i);
sfVector4f_t get_surface_normal(triangle_t triangle);
sfVector4f_t Vector_Add(sfVector4f_t v, sfVector4f_t w);
sfVector4f_t Vector_Sub(sfVector4f_t v, sfVector4f_t w);
sfVector4f_t Vector_Mul(sfVector4f_t v, float w);
sfVector4f_t Vector_Normalise(sfVector4f_t v);
float Vector_DotProduct(sfVector4f_t v, sfVector4f_t w);
void Scale_in_Screen(triangle_t *triangle);
void merge_sorting_list(link_t **list);
sfVertexArray *create_triangle(sfVector2f point1, sfVector2f point2, sfVector2f point3);

/* DRAW */
void display_triangles(link_t *mesh);

#endif /* !ENGINE_H_ */
