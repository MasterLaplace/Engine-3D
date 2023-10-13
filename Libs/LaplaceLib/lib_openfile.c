/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_openfile
*/

#ifdef __cplusplus
    #include <cstdio>
#else
    #if defined(_WIN32) || defined(_WIN64)
        #include <io.h>
        #include <stdio.h>

        #define access(__name, __type) _access(__name, __type)
        #define open(__file, __oflag) _open(__file, __oflag)
        #define F_OK 0
        #define R_OK 4
    #else
        #include <fcntl.h>
        #include <unistd.h>
        #include <stdio.h>
    #endif
#endif

inline int laplace_lib_open_file(char const *filepath, unsigned oflag)
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
