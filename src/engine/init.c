/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** init
*/

#include "engine.h"
#include "signal.h"

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
    if (read(fd, buf, st.st_size) == -1)
        return false;
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
    sfFullscreen | sfClose, NULL); // sfResize/sfFullscreen
    sfRenderWindow_setFramerateLimit(engine.window, FRAMERATE);
    sfRenderWindow_setVerticalSyncEnabled(engine.window, sfTrue);
    sfRenderWindow_setMouseCursorVisible(engine.window, sfFalse);
}

static void init_camera()
{
    engine.Pos = (sfVector4f){ 0.f, 0.f, 0.f, 1.f };
    engine.Dir = (sfVector4f){ 0.f, 0.f, 0.f, 1.f };
    engine.fawZ = 0.f;
    engine.fawY = 0.f;
    engine.fawX = 0.f;
    engine.state = IDLE;
    engine.drunkerMode = false;
    engine.size = 2.f;
}

static void init_collision()
{
    link_t *actual = engine.list_objs;
    mesh_t *mesh = NULL;
    link_t *new_mesh = NULL;
    engine.root = malloc(sizeof(Tree_t));

    if (!actual && !engine.root)
        return;
    do {
        mesh = (mesh_t *) actual->obj;
        if (mesh->type == MESH) {
            new_mesh = dup_list(mesh->lTriangle, sizeof(triangle_t));
            merge_sort_list(&new_mesh, &cmp_av_two_triangles);
            set_bvh(engine.root, new_mesh);
        }

        actual = actual->next;
    } while (engine.list_objs && actual != engine.list_objs);
}

void return_signal(UNUSED int sig)
{
    static const struct init_signal { int sig; char *msg; } signals[] = {
        {SIGPIPE, "Broken pipe"},
        {SIGINT, "Interrupt"},
        {SIGFPE, "Floating point exception"},
        {0, NULL}
    };

    for (unsigned i = 0; signals[i].msg; i++) {
        if (sig == signals[i].sig)
            printf("\r[return_signal] Signal received: %s\n", signals[i].msg);
    }
    if (sig == SIGINT)
        printf("[return_signal] Can't exit with Ctrl+C, use ESCAPE\n");
}

bool init_engine()
{
    srand(time(NULL));
    signal(SIGPIPE, return_signal);
    signal(SIGINT, return_signal);
    signal(SIGFPE, return_signal);
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
