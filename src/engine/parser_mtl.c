/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** parser_mtl
*/

#include "engine.h"

/**
 * @brief Structure contenant les informations d'un matériel (mtl)
 *
 * @param newmtl Nom du matériel
 * @param ka Couleur ambiante
 * @param kd Couleur diffuse
 * @param ks Couleur spéculaire
 * @param ke Couleur émissive
 * @param ni Densité optique
 * @param ns Specular exponent
 * @param d Transparence
 * @param illum Paramètres de lumières
 * @param map_kd Texture utilisée pour la couleur diffuse
 * @param map_ks Texture utilisée pour la couleur spéculaire
 * @param map_ka Texture utilisée pour la couleur ambiante
 */
typedef struct mtl_s {
    char *newmtl;
    sfVector3f ka;
    sfVector3f kd;
    sfVector3f ks;
    sfVector3f ke;
    float ni;
    float ns;
    float d;
    int illum;
    char *map_kd;
    char *map_ks;
    char *map_ka;
} mtl_t;

struct mtl_keys_t {
    char *key;
    char *format;
} mtl_keys[] = {
    {"newmtl", "newmtl %s"},
    {"Ka", "Ka %f %f %f"},
    {"Kd", "Kd %f %f %f"},
    {"Ks", "Ks %f %f %f"},
    {"Ke", "Ke %f %f %f"},
    {"Ni", "Ni %f"},
    {"Ns", "Ns %f"},
    {"d", "d %f"},
    {"illum", "illum %d"},
    {"map_Kd", "map_Kd %s"},
    {"map_Ks", "map_Ks %s"},
    {"map_Ka", "map_Ka %s"},
    {NULL, NULL}
};

void mtl_free(mtl_t mtl)
{
    free(mtl.newmtl);
    if (mtl.map_kd) free(mtl.map_kd);
    if (mtl.map_ks) free(mtl.map_ks);
    if (mtl.map_ka) free(mtl.map_ka);
}

void mtl_print(mtl_t mtl)
{
    printf("newmtl %s\n", mtl.newmtl);
    printf("Ka %f %f %f\n", mtl.ka.x, mtl.ka.y, mtl.ka.z);
    printf("Kd %f %f %f\n", mtl.kd.x, mtl.kd.y, mtl.kd.z);
    printf("Ks %f %f %f\n", mtl.ks.x, mtl.ks.y, mtl.ks.z);
    printf("Ke %f %f %f\n", mtl.ke.x, mtl.ke.y, mtl.ke.z);
    printf("Ni %f\nNs %f\nd %f\n", mtl.ni, mtl.ns, mtl.d);
    printf("illum %d\n", mtl.illum);
    if (mtl.map_kd) printf("map_kd %s\n", mtl.map_kd);
    if (mtl.map_ks) printf("map_ks %s\n", mtl.map_ks);
    if (mtl.map_ka) printf("map_ka %s\n", mtl.map_ka);
}

static mtl_t mtl_create_from_file(char *buffer[])
{
    mtl_t mtl = {0};
    bool new = true;

    for (; *buffer; buffer++) {
        for (unsigned i = 0; mtl_keys[i].key; i++) {
            if (!strncmp(*buffer , mtl_keys[i].key, strlen(mtl_keys[i].key))) {
                char tmp[256];
                switch (i) {
                    case 0:
                        sscanf(*buffer, mtl_keys[i].format, &tmp);
                        new = !new; if (new) return mtl;
                        mtl.newmtl = strdup(tmp);
                    break;
                    case 1: sscanf(*buffer, mtl_keys[i].format, &mtl.ka.x, &mtl.ka.y, &mtl.ka.z); break;
                    case 2: sscanf(*buffer, mtl_keys[i].format, &mtl.kd.x, &mtl.kd.y, &mtl.kd.z); break;
                    case 3: sscanf(*buffer, mtl_keys[i].format, &mtl.ks.x, &mtl.ks.y, &mtl.ks.z); break;
                    case 4: sscanf(*buffer, mtl_keys[i].format, &mtl.ke.x, &mtl.ke.y, &mtl.ke.z); break;
                    case 5: sscanf(*buffer, mtl_keys[i].format, &mtl.ni); break;
                    case 6: sscanf(*buffer, mtl_keys[i].format, &mtl.ns); break;
                    case 7: sscanf(*buffer, mtl_keys[i].format, &mtl.d); break;
                    case 8: sscanf(*buffer, mtl_keys[i].format, &mtl.illum); break;
                    case 9: sscanf(*buffer, mtl_keys[i].format, &tmp); mtl.map_kd = strdup(tmp); break;
                    case 10: sscanf(*buffer, mtl_keys[i].format, &tmp); mtl.map_ks = strdup(tmp); break;
                    case 11: sscanf(*buffer, mtl_keys[i].format, &tmp); mtl.map_ka = strdup(tmp); break;
                    default: printf("Unknown key: %s\n", mtl_keys[i].key); break;
                }
                break;
            }
        }
    }
    return mtl;
}

void loop_in_the_file(char *buffer[])
{
    for (; *buffer; buffer++) {
        if (!strncmp(*buffer, "newmtl", 6)) {
            mtl_t mtl = mtl_create_from_file(buffer);
            mtl_print(mtl);
            mtl_free(mtl);
        }
    }
}
