/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** parser_obj
*/

#include "engine.h"

mesh_t *create_obj(char **buf)
{
    mesh_t *mesh = malloc(sizeof(mesh_t));
    triangle_t *tri = NULL;
    char **info = NULL;
    sizint nb_v = 0;
    sizint j = 0;

     // count nbr of vectors
    for (register sizint i = 0; buf[i]; i++) {
        if (buf[i][0] == 'v' && buf[i][1] == ' ')
            nb_v++;
    }

    // add vectors in list
    sfVector4f_t list_v[nb_v];

    for (register sizint i = 0; buf[i]; i++) {
        if (!(info = stwa(buf[i], " ")));
        else if (info[0][0] == 'v' && info[0][1] == '\0') {
            list_v[j] = (sfVector4f_t){atof(info[1]), atof(info[2]), atof(info[3]), 1.f};
            j++;
        }
        two_free(info);
    }

    // create triangles
    mesh->lTriangle = NULL; mesh->nb_triangles = 0;

    for (register sizint i = 0; buf[i]; i++) {
        if (!(info = stwa(buf[i], " /")));
        else if (**info == 'f' && char_in_list('/', buf[i]) != -1) {
            tri = malloc(sizeof(triangle_t));
            tri->sommet[0] = list_v[atoi(info[1]) - 1];
            tri->sommet[1] = list_v[atoi(info[4]) - 1];
            tri->sommet[2] = list_v[atoi(info[7]) - 1];
            list_append(&(mesh->lTriangle), create_link(tri));
            mesh->nb_triangles++;
        }
        two_free(info);
    }
    two_free(buf);
    return mesh;
}
