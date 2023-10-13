/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_strcat_test
*/

#include <criterion/criterion.h>

#ifdef __cplusplus
    #include <cstring>
    #include <cstdlib>
#else
    #include <string.h>
    #include <stdlib.h>
#endif

char *laplace_lib_strcat(char const *dest, char const *src);

Test(laplace_lib_strcat_01, should_return_concatenated_string)
{
    char *dest = "Hello";
    char *src = "World";
    char *expected = "WorldHello";

    char *actual = laplace_lib_strcat(dest, src);
    cr_assert_str_eq(actual, expected);
    free(actual);
}

Test(laplace_lib_strcat_02, should_return_concatenated_string)
{
    char *dest = "Hello";
    char *src = " World";
    char *expected = "Hello World";

    char *actual = laplace_lib_strcat(dest, src);
    cr_assert_str_neq(actual, expected);
    free(actual);
}

Test(laplace_lib_strcat_03, should_return_concatenated_string)
{
    char *dest = " World";
    char *src = "Hello";
    char *expected = "Hello World";

    char *actual = laplace_lib_strcat(dest, src);
    cr_assert_str_eq(actual, expected);
    free(actual);
}

Test(laplace_lib_strcat_04, should_return_concatenated_string)
{
    char *dest = "Hello";
    char *src = "";
    char *expected = "Hello";

    char *actual = laplace_lib_strcat(dest, src);
    cr_assert_str_eq(actual, expected);
    free(actual);
}

Test(laplace_lib_strcat_05, should_return_concatenated_string)
{
    char *dest = "";
    char *src = "Hello";
    char *expected = "Hello";

    char *actual = laplace_lib_strcat(dest, src);
    cr_assert_str_eq(actual, expected);
    free(actual);
}
