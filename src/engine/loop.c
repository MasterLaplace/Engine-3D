/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** loop
*/

#include "engine.h"

void add_in_FinalMesh(triangle_t *triangle)
{
    triangle_t *tri = malloc(sizeof(triangle_t));
    memcpy(tri, triangle, sizeof(triangle_t));

    link_t *link = create_link(tri);
    list_append(&(engine.FinalMesh), link);
}

static void manage_triangle(mesh_t *mesh)
{
    triangle_t triTransformed, triViewed;
    link_t *actual = mesh->lTriangle;
    triangle_t *tetrimi = NULL;
    sfVector4f_t normal;

    // Set Lightening
    static sfVector4f_t light_dir = (sfVector4f_t) {0.0f, 1.0f, -1.0f, 1.0f};
    if (light_dir.z <= 0.999)
        light_dir.z += 0.005f;
    else
        light_dir.z = -1.0f;

    if (!actual)
        return;
    do {
        tetrimi = (triangle_t *) actual->obj;

        //* Model to World (M2W) */
        triTransformed.sommet[0] = Matrix_MultiplyVector(triTransformed.sommet[0], engine.ModeltoWorld, tetrimi->sommet[0]);
        triTransformed.sommet[1] = Matrix_MultiplyVector(triTransformed.sommet[1], engine.ModeltoWorld, tetrimi->sommet[1]);
        triTransformed.sommet[2] = Matrix_MultiplyVector(triTransformed.sommet[2], engine.ModeltoWorld, tetrimi->sommet[2]);

        //* Backface culling */
        // get surface normal
        normal = get_surface_normal(triTransformed);

        // get surface from View
        sfVector4f_t CameraRay = Vector_Sub(triTransformed.sommet[0], engine.Pos);

        if (Vector_DotProduct(normal, CameraRay) < 0.0f) {
            // Get Lightening
            light_dir = Vector_Normalise(light_dir);
            triViewed.dp = Vector_DotProduct(normal, light_dir);

            //* World to View (W2V) */
            triViewed.sommet[0] = Matrix_MultiplyVector(triViewed.sommet[0], engine.WorldtoView, triTransformed.sommet[0]);
            triViewed.sommet[1] = Matrix_MultiplyVector(triViewed.sommet[1], engine.WorldtoView, triTransformed.sommet[1]);
            triViewed.sommet[2] = Matrix_MultiplyVector(triViewed.sommet[2], engine.WorldtoView, triTransformed.sommet[2]);

            //* Cut to Screen (C2S) */
            clipping(triViewed);
        }
        actual = actual->next;
    } while (mesh->lTriangle && actual != mesh->lTriangle);
}

static void draw_mesh()
{
    link_t *actual = engine.list_objs;
    mesh_t *tetrimi = NULL;
    engine.FinalMesh = NULL;

    if (!actual)
        return;
    do {
        tetrimi = (mesh_t *) actual->obj;
        manage_triangle(tetrimi);
        actual = actual->next;
    } while (engine.list_objs && actual != engine.list_objs);

    merge_sorting_list(&engine.FinalMesh);
    display_triangles(engine.FinalMesh);
    clean_triangles(engine.FinalMesh);
}

static void clock_framerate()
{
    static float clock = 0.0f;
    float now = sfTime_asSeconds(sfClock_getElapsedTime(engine.clock));
    float diff = now - clock;

    vectors_3d_to_2d();

    while (diff >= (float) 1 / FRAMERATE) {
        diff -= (float) 1 / FRAMERATE;
        sfRenderWindow_clear(WINDOW, sfBlack);

        manage_move();
        draw_mesh();

        sfRenderWindow_display(WINDOW);
        clock = sfTime_asSeconds(sfClock_getElapsedTime(engine.clock));
    }
}

void loop_engine()
{
    sfEvent event;

    while (sfRenderWindow_isOpen( WINDOW )) {
        while (sfRenderWindow_pollEvent(WINDOW, &event))
            analyse_events(event);
        clock_framerate();
    }
}
