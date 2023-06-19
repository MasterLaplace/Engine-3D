/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** openfile_test
*/

#include <criterion/criterion.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int open_file(char const *filepath, unsigned oflag);

Test(open_file_01, open_file_test)
{
    int fd = open_file("tests/test_my/.file.txt", O_RDONLY);

    cr_assert_neq(fd, -1);
    close(fd);
}
