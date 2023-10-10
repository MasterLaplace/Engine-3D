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
    #include <time.h>
    #include <math.h>
    #include <string.h>
    #include "constants.h"
    #include "lib.h"
    #include "link_list.h"

    #ifdef __PIC__
    #define COMPILED_AS_SHARED_LIBRARY 1
    #else
    #define COMPILED_AS_SHARED_LIBRARY 0
    #endif

typedef struct engine_s engine_t;

typedef enum {
    IDLE,
    JUMP,
} player_state;

typedef enum {
    HIGH, LOW, WATER, BUBBLE, NONE
} texture;

typedef enum {
    MAP, WAVE, MESH, PLAYER
} mesh_type;


/// @brief x, y, z, w
typedef struct {
    float x, y, z, w;
} sfVector4f;

typedef struct {
	float m[4][4];
} matrix;

/**
 * @brief  Structure d'un triangle
 *
 * @param sommet Sommets du triangle (x, y, z, w)
 * @param texture Coordonnées de texture du triangle (x, y, z)
 * @param usemtl Texture utilisée
 * @param dp Distance par rapport à la caméra
 */
typedef struct triangle_s {
    sfVector4f sommet[3];
    sfVector3f texture[3];
    texture usemtl;
    float dp;
} triangle_t;

/**
 * @brief  Structure d'une vague (gerstner)
 *
 * @param dp Distance par rapport à la caméra
 * @param A Amplitude de la vague (entre 0 et 1)
 * @param wavelength Longueur d'onde de la vague
 * @param wave_speed Vitesse de la vague
 * @param wave_direction Direction de la vague (en radian)
 * @param k Constante de la vague (2 * PI / wavelength)
 * @param omega Constante de la vague (k * wave_speed)
 */
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

typedef struct Tree_s {
    struct Tree_s *node[4]; // node
    sfVector3f s_g[2]; // smaller/greater vectors
    triangle_t *triangle; // triangle at front node
} Tree_t;

union vector
{
    sfVector3f vec3;
    sfVector4f vec4;
};

struct engine_s {
    /*graphic*/
    sfRenderWindow *window;
    sfClock *clock;
    sfRenderStates **textures;
    sfImage **images;
    /*camera*/
    sfVector4f Pos;
    sfVector4f Dir;
    float fawZ;
    float fawY;
    float fawX;
    bool drunkerMode;
    /*player*/
    player_state state;
    sizint size;
    /*matrix*/
    float ModeltoWorld[4][4];
    float WorldtoView[4][4];
    float ViewtoProjection[4][4];
    /*link*/
    link_t *list_objs;
    link_t *FinalMesh;
    /*collide*/
    Tree_t *root;
    sfVector3f s_g[2];
    /*water*/
    link_t *wave_list;
    float t;  // Temps
};

extern engine_t engine;

/* INIT */
bool open_folder(char *path);
bool init_engine();
sfRenderStates **init_textures();
sfImage **init_images();

/* CLEAN */
void clean_triangles(link_t *mesh);
void destroying();

/* PARSER OBJ */
mesh_t *create_obj(char **buf);

#ifdef COMPILED_AS_SHARED_LIBRARY
    #define EXPORT __attribute__((visibility("default")))
/* HELP */
bool print_help(int ac, char const *av[]);
#endif

/* LOOP */
void loop_engine();
void add_in_FinalMesh(triangle_t *triangle);

/* EVENT */
void analyse_events(sfEvent event);
void manage_move();

/* RASTERIZEING */
void vectors_3d_to_2d(bool drunkerMode);
void Mesh_Transform(sfVector4f pos, sfVector3f angle, sfVector3f scale);
void Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
sfVector4f get_surface_normal(triangle_t triangle);
void Scale_in_Screen(triangle_t *triangle);
bool cmp_two_triangles(void *triangle_1, void *triangle_2);
bool cmp_av_two_triangles(void *triangle_1, void *triangle_2);

/* CLIPPING */
void clipping(triangle_t triangle);

/* UTILS */
sfVector4f Vector_Add(sfVector4f v, sfVector4f w);
sfVector4f Vector_Sub(sfVector4f v, sfVector4f w);
sfVector4f Vector_Mul(sfVector4f v, float w);
sfVector4f Vector_Div(sfVector4f v, float w);
sfVector4f Vector_Normalise(sfVector4f v);
sfVector4f Vector_CrossProduct(sfVector4f a, sfVector4f b);
sfVector4f Matrix_MultiplyVector(sfVector4f v, float (*m)[4], sfVector4f w);
sfVector4f Vector_intersectPlane(sfVector4f p, sfVector4f n, sfVector4f Start, sfVector4f End, float *t);
float Vector_DotProduct(sfVector4f v, sfVector4f w);
float Vector_Length(sfVector4f v);
float calcul_dist(sfVector4f p, sfVector4f pp, sfVector4f n);
void Matrix_Multiply(float (*m)[4], float (*m1)[4], float (*m2)[4]);
matrix Matrix_QuickInverse(float (*m)[4]);
sfVector3f average_triangle(triangle_t *t);
void print_vector(sfVector4f v);
void print_triangle(triangle_t *t);
void print_cube(sfVector3f s_g[2]);

/* DRAW */
void display_triangles(link_t *mesh);

/* BVH */
void set_bvh(Tree_t *tree, link_t *mesh);
sfVector3f get_bvh(Tree_t *tree, sfVector4f point);
void print_bvh(Tree_t *tree);

/* WATER */
void init_wave();
void create_water(sizint Xmax, sizint Ymax);
void superpose_waves(link_t *list);
void clean_wave();

#endif /* !ENGINE_H_ */
