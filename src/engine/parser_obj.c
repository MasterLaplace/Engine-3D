/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** parser_obj
*/

#include "engine.h"

extern const sizint NB_TEXTURES;
extern const char *TEXTURE_PATHS[];
extern const sizint NB_MTL;
extern const char *MTL_PATHS[];

static char *search_in_mtl_file(const char *filepathname, const char *texture_name)
{
    static bool found = false;
    struct stat st;
    char *buf = NULL;
    int fd = open_file(filepathname, O_RDONLY);
    char *map_Kd = NULL;

    if (fd == -1)
        return map_Kd;
    stat(filepathname, &st);
    if (!(buf = malloc(sizeof(char) * (st.st_size + 1))))
        return map_Kd;
    read(fd, buf, st.st_size);
    buf[st.st_size] = '\0';
    char **info = stwa(buf, "\n");

    for (register sizint i = 0; info[i]; i++) {
        if (!found && strstr(info[i], texture_name)) {
            found = true;
        } else if (found && strncmp(info[i], "map_Kd", 6) == 0) {
            char **Kd = stwa(info[i], " ");
            map_Kd = strdup(Kd[1]);
            two_free(Kd);
            break;
        }
    }
    found = false;
    free(buf);
    two_free(info);
    close(fd);
    return map_Kd;
}

static sizint search_in_file(const char *texture_name, char *filename)
{
    char *texture_file = NULL;

    // find the good mtl file
    for (sizint i = 0; i < NB_MTL; i++) {
        if (strstr((char *)MTL_PATHS[i], filename)) {
            // find the good texture_name with newmtl
            // get texture_file from map_Kd variable
            texture_file = search_in_mtl_file(MTL_PATHS[i], texture_name);
            break;
        }
    }
    if (!texture_file)
        return 0;
    // find the good png file
    for (sizint i = 0; i < NB_TEXTURES; i++) {
        if (strstr((char *)TEXTURE_PATHS[i], texture_file)) {
            free(texture_file);
            printf("Texture_path: %s\n", TEXTURE_PATHS[i]);
            return i;
        }
    }
    free(texture_file);
    return 0;
}


mesh_t *create_obj(char **buf)
{
    mesh_t *mesh = malloc(sizeof(mesh_t));
    triangle_t *tri, *tri2 = NULL;
    char **info = NULL;
    size_t nb_chr = 0;
    sizint nb_v = 0, nb_vt = 0;

     // count nbr of vectors
    for (register sizint i = 0; buf[i]; i++) {
        if (buf[i][0] == 'v' && buf[i][1] == ' ')
            nb_v++;
        else if (buf[i][0] == 'v' && buf[i][1] == 't')
            nb_vt++;
    }

    // add vectors in list
    sfVector4f_t list_v[nb_v];
    sfVector3f list_vt[nb_vt];

    for (register sizint i = 0, v = 0, t = 0; buf[i]; i++) {
        if (!(info = stwa(buf[i], " ")));
        else if (info[0][0] == 'v' && info[0][1] == '\0') {
            list_v[v] = (sfVector4f_t){atof(info[1]), atof(info[2]), atof(info[3]), 1.f};
            v++;
        } else if (info[0][0] == 'v' && info[0][1] == 't') {
            list_vt[t] = (sfVector3f){atof(info[1]), atof(info[2]), 1.f};
            t++;
        }
        two_free(info);
    }

    // create triangles
    mesh->lTriangle = NULL; mesh->nb_triangles = 0;
    char *mtllib = NULL;
    sizint tex = 0;

    for (register sizint i = 0; buf[i]; i++) {
        if (!(info = stwa(buf[i], " /")));
        else if (**info == 'f' && (nb_chr = count_char(buf[i], '/')) != 0) {
            tri = malloc(sizeof(triangle_t));
            tri->sommet[0] = list_v[atoi(info[1]) - 1];
            tri->sommet[1] = list_v[atoi(info[(nb_chr % 3 == 0 && nb_chr != 3)?4:3]) - 1];
            tri->sommet[2] = list_v[atoi(info[(nb_chr % 3 == 0 && nb_chr != 3)?7:5]) - 1];
            tri->texture[0] = list_vt[atoi(info[2]) - 1];
            tri->texture[1] = list_vt[atoi(info[(nb_chr % 3 == 0 && nb_chr != 3)?5:4]) - 1];
            tri->texture[2] = list_vt[atoi(info[(nb_chr % 3 == 0 && nb_chr != 3)?8:6]) - 1];
            tri->usemtl = tex;
            list_append(&(mesh->lTriangle), create_link(tri));
            mesh->nb_triangles++;
            if (info[(nb_chr % 3 == 0 && nb_chr != 3)?10:7]) {
                tri2 = malloc(sizeof(triangle_t));
                tri2->sommet[0] = list_v[atoi(info[1]) - 1];
                tri2->sommet[1] = list_v[atoi(info[(nb_chr % 3 == 0 && nb_chr != 3)?7:5]) - 1];
                tri2->sommet[2] = list_v[atoi(info[(nb_chr % 3 == 0 && nb_chr != 3)?10:7]) - 1];
                tri2->texture[0] = list_vt[atoi(info[2]) - 1];
                tri2->texture[1] = list_vt[atoi(info[(nb_chr % 3 == 0 && nb_chr != 3)?8:6]) - 1];
                tri2->texture[2] = list_vt[atoi(info[(nb_chr % 3 == 0 && nb_chr != 3)?11:8]) - 1];
                tri2->usemtl = tex;
                list_append(&(mesh->lTriangle), create_link(tri2));
                mesh->nb_triangles++;
            }
        } else if (strcmp(info[0], "usemtl") == 0)
            tex = search_in_file(info[1], mtllib);
        else if (strcmp(info[0], "mtllib") == 0)
            mtllib = strdup(info[1]);
        two_free(info);
    }
    free(mtllib);
    return mesh;
}
