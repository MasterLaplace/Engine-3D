/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** loop
*/

#include "engine.h"
#include "WorldPartition.h"

void add_in_FinalMesh(triangle_t *triangle)
{
    triangle_t *tri = malloc(sizeof(triangle_t));
    memcpy(tri, triangle, sizeof(triangle_t));

    link_t *link = create_link(tri);
    list_append(&(engine.FinalMesh), link);
}

static void manage_triangle(link_t *mesh)
{
    triangle_t triTransformed, triViewed;
    link_t *actual = mesh;
    triangle_t *tetrimi = NULL;
    sfVector4f normal;

    // Set Lightening
    static sfVector4f light_dir = (sfVector4f){0.0f, 1.0f, -1.0f, 1.0f};
    // if (light_dir.z <= 0.999)
    //     light_dir.z += 0.005f;
    // else
    //     light_dir.z = -1.0f;

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
        sfVector4f CameraRay = Vector_Sub(triTransformed.sommet[0], engine.Pos);

        if (Vector_DotProduct(normal, CameraRay) < 0.0f || tetrimi->usemtl == NONE) {
            // Get Lightening
            light_dir = Vector_Normalise(light_dir);
            triViewed.dp = Vector_DotProduct(normal, light_dir);

            //* World to View (W2V) */
            triViewed.sommet[0] = Matrix_MultiplyVector(triViewed.sommet[0], engine.WorldtoView, triTransformed.sommet[0]);
            triViewed.sommet[1] = Matrix_MultiplyVector(triViewed.sommet[1], engine.WorldtoView, triTransformed.sommet[1]);
            triViewed.sommet[2] = Matrix_MultiplyVector(triViewed.sommet[2], engine.WorldtoView, triTransformed.sommet[2]);
            triViewed.texture[0] = tetrimi->texture[0];
            triViewed.texture[1] = tetrimi->texture[1];
            triViewed.texture[2] = tetrimi->texture[2];
            triViewed.usemtl = tetrimi->usemtl;

            //* Cut to Screen (C2S) */
            clipping(triViewed);
        }
        actual = actual->next;
    } while (mesh && actual != mesh);
}

static __attribute__((optimize(0))) void draw_mesh()
{
    link_t *actual = engine.list_objs;
    mesh_t *mesh = NULL;
    engine.FinalMesh = NULL;

    if (!actual)
        return;
    do {
        mesh = (mesh_t *) actual->obj;
        if (mesh->type == WAVE)
            superpose_waves(mesh->lTriangle);
        if (mesh->type == PLAYER) {
            sfVector4f Forward = Vector_Mul(engine.Dir, 2);
            Mesh_Transform(
                Vector_Add(engine.Pos, (sfVector4f){Forward.x, -0.5, Forward.z, 1}),
                (sfVector3f){0, engine.fawY, engine.fawZ},
                (sfVector3f){1, 1, 1});
        #ifdef DEBUG_MODE
        } else if (mesh->type == WAVE) {
            Mesh_Transform(
                (sfVector4f){20, -12, 80, 1},
                (sfVector3f){0, 0, 0},
                (sfVector3f){1, 1, 1});
        #endif
        } else {
            Mesh_Transform(
                (sfVector4f){0, 0, 0, 1},
                (sfVector3f){0, 0, 0},
                (sfVector3f){1, 1, 1});
        }
        manage_triangle(mesh->lTriangle);
        actual = actual->next;
    } while (engine.list_objs && actual != engine.list_objs);

    merge_sort_list(&engine.FinalMesh, &cmp_two_triangles);

    if (!engine.FinalMesh)
        return;
    while (engine.FinalMesh) {
        triangle_t *triToRaster = (triangle_t *) engine.FinalMesh->obj;

        triangle_t clipped[2] = {0};
        link_t *listTriangles = NULL;
        list_append(&listTriangles, create_link(triToRaster));
        int nNewTriangles = 1;

        for (int p = 0; p < 4; p++)
        {
            int nTrisToAdd = 0;
            while (nNewTriangles > 0)
            {
                triangle_t test = *(triangle_t *) listTriangles->obj;
                free(listTriangles->obj);
                listTriangles->obj = NULL;
                list_remove(&listTriangles, listTriangles, NULL);
                nNewTriangles--;

                switch (p)
                {
                case 0: nTrisToAdd = Triangle_ClipAgainstPlane((sfVector4f){0.0f, 0.0f, 0.0f, 1.0f}, (sfVector4f){0.0f, 1.0f, 0.0f, 1.0f}, &test, &clipped); break;
                case 1: nTrisToAdd = Triangle_ClipAgainstPlane((sfVector4f){0.0f, (float)WIN_Y - 1, 0.0f, 1.0f}, (sfVector4f){0.0f, -1.0f, 0.0f, 1.0f}, &test, &clipped); ;break;
                case 2: nTrisToAdd = Triangle_ClipAgainstPlane((sfVector4f){0.0f, 0.0f, 0.0f, 1.0f}, (sfVector4f){1.0f, 0.0f, 0.0f, 1.0f}, &test, &clipped); break;
                case 3: nTrisToAdd = Triangle_ClipAgainstPlane((sfVector4f){(float)WIN_X - 1, 0.0f, 0.0f, 1.0f}, (sfVector4f){-1.0f, 0.0f, 0.0f, 1.0f}, &test, &clipped); break;
                }

                for (int w = 0; w < nTrisToAdd; w++) {
                    triangle_t *tri = malloc(sizeof(triangle_t));
                    memcpy(tri, &clipped[w], sizeof(triangle_t));
                    list_append(&listTriangles, create_link(tri));
                }
            }
            nNewTriangles = len_link(listTriangles);
        }

        while (listTriangles) {
            triangle_t *tri = (triangle_t *) listTriangles->obj;
            draw_triangle(tri);
            free((triangle_t *) listTriangles->obj);
            list_remove(&listTriangles, listTriangles, NULL);
        }

        list_remove(&(engine.FinalMesh), engine.FinalMesh, NULL);
    }

    // display_triangles(engine.FinalMesh);
    // clean_triangles(engine.FinalMesh);
}

static void clock_framerate()
{
    #ifndef DEBUG
    static float clock = 0.0f;
    #endif
    engine.t = sfTime_asSeconds(sfClock_getElapsedTime(engine.clock));
    #ifndef DEBUG
    float diff = engine.t - clock;
    #endif

    vectors_3d_to_2d(engine.drunkerMode);

    #ifndef DEBUG
    while (diff >= (float) 1 / FRAMERATE) {
        diff -= (float) 1 / FRAMERATE;
        #endif
        sfRenderWindow_clear(WINDOW, sfCyan);

        manage_move();
        // get_bvh(engine.root, &(engine.Pos), engine.radius);

        world_partition_update(engine.world, (sfVector2f){engine.Pos.x, engine.Pos.z}, 200);
        r_tree_t *tree = world_partition_get_chunk_data(engine.world, (sfVector2f){engine.Pos.x, engine.Pos.z});
        r_tree_check_collision(tree, &(engine.Pos), engine.radius);
        draw_mesh();
        #ifdef DEBUG_MODE
        clean_cube_box_from_list();
        #endif

        sfRenderWindow_display(WINDOW);
        #ifdef DEBUG
        sfImage *image = sfRenderWindow_capture(WINDOW);
        sfImage_saveToFile(image, "screenshot.png");
        sfImage_destroy(image);
        #endif
    #ifndef DEBUG
        clock = sfTime_asSeconds(sfClock_getElapsedTime(engine.clock));
    }
    #endif
}

void loop_engine()
{
    sfEvent event;

    while (sfRenderWindow_isOpen( WINDOW )) {
        while (sfRenderWindow_pollEvent(WINDOW, &event))
            analyse_events(event);
        clock_framerate();
        #ifdef DEBUG
        return;
        #endif
    }
}
