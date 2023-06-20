/*
** ME PROJECT, 2022
** DEN-GINER-Master-Laplace
** File description:
** init_textures
*/

#include "engine.h"

extern const sizint NB_TEXTURES;
extern const char *TEXTURE_PATHS[];
static const char load_error[] = "Error: Failed to load textures Please reset the game folder.\n";

sfRenderStates **init_textures()
{
    sfRenderStates **textures = malloc(sizeof(sfRenderStates *) * (NB_TEXTURES + 1));

    if (!textures)
        return (NULL);
    for (sizint i = 0; i < NB_TEXTURES; i++) {
        textures[i] = malloc(sizeof(sfRenderStates));
        textures[i]->blendMode = sfBlendAlpha;
        textures[i]->transform = sfTransform_Identity;
        textures[i]->texture = sfTexture_createFromFile(TEXTURE_PATHS[i], NULL);
        textures[i]->shader = NULL;
        if (!textures[i]) {
            perror(load_error);
            return NULL;
        }
    }
    textures[NB_TEXTURES] = NULL;
    return textures;
}

sfImage **init_images()
{
    sfImage **images = malloc(sizeof(sfImage *) * (NB_TEXTURES + 1));

    if (!images)
        return (NULL);
    for (sizint i = 0; i < NB_TEXTURES; i++) {
        images[i] = sfImage_createFromFile(TEXTURE_PATHS[i]);
        if (!images[i])
            return (NULL);
    }
    images[NB_TEXTURES] = NULL;
    return images;
}
