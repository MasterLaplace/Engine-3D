/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** perlin
*/

#include "engine.h"

void init_perlin()
{
    engine.perlin.octaves = 3;
    engine.perlin.frequence = 4;
    engine.perlin.persistence = 0.1;
    engine.perlin.lissage = 3;
    engine.perlin.NoiseSeed[MAP_Y];
    for (sizint i = 0; i < MAP_Y; i++) {
        engine.perlin.NoiseSeed[i] = (float)rand() / (float)RAND_MAX;
    }
}

void PerlinNoise1D(int nCount, float *fSeed, int nOctaves, float *fOut)
{
    for (int x = 0; x < nCount; x++) {
        float fNoise = 0.0f;
        float fScaleAcc = 0.0f;
        float fScale = 1.0f;
        for (int o = 0; o < nOctaves; o++) {
            int nPitch = nCount >> o;
            int nSample1 = (x / nPitch) * nPitch;
            int nSample2 = (nSample1 + nPitch) % nCount;
            float fBlend = (float)(x - nSample1) / (float)nPitch;
            float fSample = (1.0f - fBlend) * fSeed[nSample1] + fBlend * fSeed[nSample2];
            fScaleAcc += fScale;
            fNoise += fSample * fScale;
            fScale = fScale / engine.perlin.persistence;
        }
        fOut[x] = fNoise / fScaleAcc;
    }
}

void create_map(sizint Xmax, sizint Ymax)
{
    mesh_t *mesh = malloc(sizeof(mesh_t));
    triangle_t *tri, *tri2 = NULL;
    mesh->lTriangle = NULL; mesh->nb_triangles = 0; mesh->type = MAP;

    for (sizint i = 0; i < Ymax; i++) {
        for (sizint j = 0; j < Xmax; j++) {
            tri = malloc(sizeof(triangle_t));
            tri->sommet[0] = (sfVector4f){j + 1, 0, i + 1, 1};
            tri->sommet[1] = (sfVector4f){j + 1, 0, i, 1};
            tri->sommet[2] = (sfVector4f){j, 0, i, 1};
            tri->texture[0] = (sfVector3f){35, 35, 1};
            tri->texture[1] = (sfVector3f){35, 0, 1};
            tri->texture[2] = (sfVector3f){0, 0, 1};
            tri->usemtl = BUBBLE;
            list_append(&(mesh->lTriangle), create_link(tri));
            mesh->nb_triangles++;

            // tri2 = malloc(sizeof(triangle_t));
            // tri2->sommet[0] = (sfVector4f){j, 0, i, 1};
            // tri2->sommet[1] = (sfVector4f){j, 0, i + 1, 1};
            // tri2->sommet[2] = (sfVector4f){j + 1, 0, i + 1, 1};
            // tri2->texture[0] = (sfVector3f){0, 0, 1};
            // tri2->texture[1] = (sfVector3f){0, 35, 1};
            // tri2->texture[2] = (sfVector3f){35, 35, 1};
            // tri2->usemtl = BUBBLE;
            // list_append(&(mesh->lTriangle), create_link(tri2));
        }
    }
    list_append(&(LIST_OBJS), create_link(mesh));
}
