/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** Azir 0.1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void create_folder

void create_layer(char *str)
{
    // create a directory
    unsigned int len = strlen(str);
    char command[len + 50];

    sprintf(command, "mkdir ./assets/layer_%s", str);
    system(command);
    memset(command, 0, len + 50);

    // create a subdirectory
    sprintf(command, "mkdir ./assets/layer_%s/MAP", str);
    system(command);
    memset(command, 0, len + 50);
    sprintf(command, "touch ./assets/layer_%s/MAP/.gitkeep", str);
    system(command);
    memset(command, 0, len + 50);
    sprintf(command, "mkdir ./assets/layer_%s/MESH", str);
    system(command);
    memset(command, 0, len + 50);
    sprintf(command, "touch ./assets/layer_%s/MESH/.gitkeep", str);
    system(command);
}

void clean(char *str)
{
    char command[strlen(str) + 25];
    sprintf(command, "rm -rf ./assets/layer_%s", str);
    system(command);
}

void help()
{
    printf("USAGE : ./manager [help|clean|create] [layer_name]\n");
}

int main(int ac, char **av)
{
    if (ac < 2)
        return 84;
    if (strcmp(av[1], "help") == 0) {
        help();
        return 0;
    } else if (strcmp(av[1], "clean") == 0) {
        clean(av[2]);
        return 0;
    } else if (strcmp(av[1], "create") == 0) {
        create_layer(av[2]);
    }
    return 0;
}
