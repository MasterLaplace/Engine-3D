/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** openfile
*/

#include "my.h"

int open_file(char const *filepath, int oflag)
{
    int fd = open(filepath, oflag);

    if (!filepath)
        return (-1);
    if (access(filepath, F_OK) || fd == -1) {
        printf("no such file or directory\n");
        return (-1);
    }
    if (access(filepath, R_OK)) {
        printf("Don't have the permission to read the file %s", filepath);
        return (-1);
    }
    return fd;
}
