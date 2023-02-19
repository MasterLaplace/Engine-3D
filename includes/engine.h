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

typedef enum {
    IDLE,
    JUMP,
} player_state;

typedef enum {
    HIGH, LOW, WATER, BUBBLE, NONE
} texture;

typedef enum {
    WAVE, MESH
} mesh_type;


/// @brief x, y, z, w
typedef struct sfVector4f_s {
    float x, y, z, w;
} sfVector4f_t;

typedef struct matrix {
	float m[4][4];
} matrix;

typedef struct triangle_s {
    sfVector4f_t sommet[3];
    sfVector3f texture[3];
    texture usemtl;
    float dp;
} triangle_t;

typedef struct wave_s {
    float dp;
    float A;
    float wavelength;
    float wave_speed;
    float wave_direction;
    float k;
    float omega;
} wave_t;

typedef struct mesh_s {
    link_t *lTriangle;
    sizint nb_triangles;
    mesh_type type;
} mesh_t;


struct engine_s {
    /*graphic*/
    sfRenderWindow *window;
    sfClock *clock;
    sfRenderStates **textures;
    sfImage **images;
    /*camera*/
    sfVector4f_t Pos;
    sfVector4f_t Dir;
    float fawZ;
    float fawY;
    float fawX;
    /*player*/
    player_state state;
    /*matrix*/
    float ModeltoWorld[4][4];
    float WorldtoView[4][4];
    float ViewtoProjection[4][4];
    /*link*/
    link_t *list_objs;
    link_t *FinalMesh;
    /*water*/
    link_t *wave_list;
    float t;  // Temps
};

extern engine_t engine;

/* INIT */
bool open_folder(char *path);
bool init_engine();
void display_init();
sfRenderStates **init_textures();
sfImage **init_images();

/* CLEAN */
void clean_triangles(link_t *mesh);
void destroying();

/* PARSER OBJ */
mesh_t *create_obj(char **buf);

/* HELP */
bool print_help(int ac, char const *av[]);

/* LOOP */
void loop_engine();
void add_in_FinalMesh(triangle_t *triangle);

/* EVENT */
void analyse_events(sfEvent event);
void manage_move();

/* RASTERIZEING */
void vectors_3d_to_2d();
void Mesh_Transform(sfVector3f pos);
void Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
sfVector4f_t get_surface_normal(triangle_t triangle);
void Scale_in_Screen(triangle_t *triangle);
void merge_sorting_list(link_t **list);

/* CLIPPING */
void clipping(triangle_t triangle);

/* UTILS */
sfVector4f_t Vector_Add(sfVector4f_t v, sfVector4f_t w);
sfVector4f_t Vector_Sub(sfVector4f_t v, sfVector4f_t w);
sfVector4f_t Vector_Mul(sfVector4f_t v, float w);
sfVector4f_t Vector_Div(sfVector4f_t v, float w);
sfVector4f_t Vector_Normalise(sfVector4f_t v);
sfVector4f_t Vector_CrossProduct(sfVector4f_t a, sfVector4f_t b);
sfVector4f_t Matrix_MultiplyVector(sfVector4f_t v, float (*m)[4], sfVector4f_t w);
sfVector4f_t Vector_intersectPlane(sfVector4f_t p, sfVector4f_t n, sfVector4f_t Start, sfVector4f_t End, float *t);
float Vector_DotProduct(sfVector4f_t v, sfVector4f_t w);
float Vector_Length(sfVector4f_t v);
float calcul_dist(sfVector4f_t p, sfVector4f_t pp, sfVector4f_t n);
void Matrix_Multiply(float (*m)[4], float (*m1)[4], float (*m2)[4]);
matrix Matrix_QuickInverse(float (*m)[4]);

/* DRAW */
void display_triangles(link_t *mesh);

/* WATER */
void init_wave();
void superpose_waves(link_t *list);
void clean_wave();

#endif /* !ENGINE_H_ */
