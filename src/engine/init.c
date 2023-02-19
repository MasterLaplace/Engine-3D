/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** init
*/

#include "engine.h"

static bool load_file(char *filename, char *filepath)
{
    struct stat st;
    char *file = my_strcat(filename, filepath);
    char *buf = NULL;
    int fd = open_file(file, O_RDONLY);

    if (fd == -1)
        return false;
    stat(file, &st);
    if (!(buf = malloc(sizeof(char) * (st.st_size + 1))))
        return false;
    read(fd, buf, st.st_size);
    buf[st.st_size] = '\0';
    list_append(&(LIST_OBJS), create_link(create_obj(stwa(buf, "\n"))));
    free(buf);
    free(file);
    close(fd);
    return true;
}

bool open_folder(char *path)
{
    DIR *dp = NULL;
    struct dirent *dirp = NULL;

    LIST_OBJS = NULL;
    if (!(dp = opendir(path)))
        return false;
    while ((dirp = readdir(dp))) {
        if (dirp->d_name[0] == '.' || !(strstr(dirp->d_name, ".obj")))
            continue;
        if (!load_file(dirp->d_name, path)) {
            closedir(dp);
            return false;
        }
    }
    closedir(dp);
    return true;
}

static void display_init()
{
    sfVideoMode mode = {WIN_X, WIN_Y, 32};

    engine.window = sfRenderWindow_create(mode, "Engine-3D",
    sfResize | sfClose, NULL); // sfResize/sfFullscreen
    sfRenderWindow_setFramerateLimit(engine.window, FRAMERATE);
}

static void init_camera()
{
    engine.Pos = (sfVector4f_t){ 0.f, 0.f, 0.f, 1.f};
    engine.Dir = (sfVector4f_t){ 0.f, 0.f, 0.f, 1.f};
    engine.fawZ = 0.f;
    engine.fawY = 0.f;
    engine.fawX = 0.f;
    engine.state = IDLE;
    engine.size = 4;
}

static void init_collision()
{
    link_t *actual = engine.list_objs;
    mesh_t *mesh = NULL;
    engine.root = NULL;

    if (!actual)
        return;
    do {
        mesh = (mesh_t *) actual->obj;
        if (actual != engine.list_objs && mesh->type != WAVE)
            set_bvh(mesh->lTriangle);

        actual = actual->next;
    } while (engine.list_objs && actual != engine.list_objs);
}

bool init_engine()
{
    /*graphic*/
    display_init();
    engine.clock = sfClock_create();
    engine.textures = init_textures();
    engine.images = init_images();
    /*wave*/
    init_wave();
    create_water(MAP_X, MAP_Y);
    /*camera*/
    init_camera();
    /*collide*/
    init_collision();
    /*matrix*/
    memset(engine.ModeltoWorld, 0.f, sizeof(engine.ModeltoWorld));
    memset(engine.WorldtoView, 0.f, sizeof(engine.WorldtoView));
    // View to Projection (V2P)
    memset(engine.ViewtoProjection, 0.f, sizeof(engine.ViewtoProjection));
    Matrix_MakeProjection(90.0f, (float) WIN_Y / (float) WIN_X, 0.1f, 1000.0f);
    if (WINDOW && engine.textures && engine.images)
        return true;
    return false;
}
