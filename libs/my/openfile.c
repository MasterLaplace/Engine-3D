/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** openfile
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int open_file(char const *filepath, unsigned oflag)
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
