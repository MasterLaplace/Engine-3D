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
        if (dirp->d_name[0] == '.' || !(find_str(dirp->d_name, ".obj")))
            continue;
        if (!load_file(dirp->d_name, path)) {
            closedir(dp);
            return false;
        }
    }
    closedir(dp);
    return true;
}

void display_init()
{
    sfVideoMode mode = {WIN_X, WIN_Y, 32};

    engine.window = sfRenderWindow_create(mode, "Engine-3D",
    sfResize | sfClose, NULL); // sfResize/sfFullscreen
    sfRenderWindow_setFramerateLimit(engine.window, FRAMERATE);
}
