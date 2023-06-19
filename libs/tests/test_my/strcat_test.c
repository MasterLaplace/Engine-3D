/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** strcat_test
*/

#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>

char *my_strcat(char const *dest, char const *src);

Test(my_strcat_01, should_return_concatenated_string)
{
    char *dest = "Hello";
    char *src = "World";
    char *expected = "WorldHello";

    char *actual = my_strcat(dest, src);
    cr_assert_str_eq(actual, expected);
    free(actual);
}

Test(my_strcat_02, should_return_concatenated_string)
{
    char *dest = "Hello";
    char *src = " World";
    char *expected = "Hello World";

    char *actual = my_strcat(dest, src);
    cr_assert_str_neq(actual, expected);
    free(actual);
}

Test(my_strcat_03, should_return_concatenated_string)
{
    char *dest = " World";
    char *src = "Hello";
    char *expected = "Hello World";

    char *actual = my_strcat(dest, src);
    cr_assert_str_eq(actual, expected);
    free(actual);
}

Test(my_strcat_04, should_return_concatenated_string)
{
    char *dest = "Hello";
    char *src = "";
    char *expected = "Hello";

    char *actual = my_strcat(dest, src);
    cr_assert_str_eq(actual, expected);
    free(actual);
}

Test(my_strcat_05, should_return_concatenated_string)
{
    char *dest = "";
    char *src = "Hello";
    char *expected = "Hello";

    char *actual = my_strcat(dest, src);
    cr_assert_str_eq(actual, expected);
    free(actual);
}
