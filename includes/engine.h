/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** engine
*/

#ifndef ENGINE_H_
    #define ENGINE_H_
    #define LIST_OBJS engine.list_objs
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
    link_t *list_objs;
};

extern engine_t engine;

/* INIT */
bool open_folder(char *path);

/* CLEAN */
void destroying();

/* PARSER OBJ */
mesh_t *create_obj(char **buf);

#endif /* !ENGINE_H_ */
