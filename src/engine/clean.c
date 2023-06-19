/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** clean
*/

#include "engine.h"

extern const sizint NB_TEXTURES;

void clean_triangles(link_t *mesh)
{
    if (!mesh)
        return;
    while (mesh) {
        free((triangle_t *) mesh->obj);
        list_remove(&(mesh), mesh, NULL);
    }
}

void clean_mesh()
{
    if (!LIST_OBJS)
        return;
    while (LIST_OBJS) {
        clean_triangles((link_t *)((mesh_t *) LIST_OBJS->obj)->lTriangle);
        free((mesh_t *) LIST_OBJS->obj);
        list_remove(&(LIST_OBJS), LIST_OBJS, NULL);
    }
}

void destroy_textures()
{
    for (sizint i = 0; i < NB_TEXTURES; i++) {
        sfTexture_destroy((sfTexture* )engine.textures[i]->texture);
        free(engine.textures[i]);
    }
    free(engine.textures);
}

void destroy_images()
{
    for (sizint i = 0; i < NB_TEXTURES; i++)
        sfImage_destroy(engine.images[i]);
    free(engine.images);
}

void clean_wave()
{
    if (!engine.wave_list)
        return;
    while (engine.wave_list) {
        free((wave_t *) engine.wave_list->obj);
        list_remove(&(engine.wave_list), engine.wave_list, NULL);
    }
}

void destroying()
{
    sfClock_destroy(engine.clock);
    sfRenderWindow_destroy(WINDOW);
    clean_mesh();
    destroy_textures();
    destroy_images();
    clean_wave();
}
