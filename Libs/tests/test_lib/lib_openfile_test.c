/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_openfile_test
*/

#include <criterion/criterion.h>

#if defined(_WIN32) || defined(__WIN32__)
    #include <io.h>

    #define close(__fd) _close(__fd)
#else
    #include <fcntl.h>
    #include <unistd.h>
#endif

int laplace_lib_open_file(char const *filepath, unsigned oflag);

Test(laplace_lib_open_file_01, laplace_lib_open_file_test)
{
    int fd = laplace_lib_open_file("tests/test_my/.file.txt", O_RDONLY);

    cr_assert_neq(fd, -1);
    close(fd);
}
