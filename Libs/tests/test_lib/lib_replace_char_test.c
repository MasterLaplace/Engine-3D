/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_replace_char_test
*/

#include <criterion/criterion.h>

#ifdef __cplusplus
    #include <cstring>
#else
    #include <string.h>
#endif

void laplace_lib_replace_char(char *str, char orig, char rep);

Test(laplace_lib_replace_char_01, should_return_true)
{
    char str[] = "Hello World";

    laplace_lib_replace_char(str, 'o', 'a');
    cr_assert_str_eq(str, "Hella Warld");
}

Test(laplace_lib_replace_char_02, should_return_true)
{
    char str[] = "Hello World";

    laplace_lib_replace_char(str, 'l', 'a');
    cr_assert_str_eq(str, "Heaao Worad");
}

Test(laplace_lib_replace_char_03, should_return_true)
{
    char str[] = "Hello World";

    laplace_lib_replace_char(str, 'H', 'a');
    cr_assert_str_eq(str, "aello World");
}

Test(laplace_lib_replace_char_04, should_return_true)
{
    char str[] = "Hello World";

    laplace_lib_replace_char(str, 'W', 'a');
    cr_assert_str_eq(str, "Hello aorld");
}

Test(laplace_lib_replace_char_05, should_return_true)
{
    char str[] = "Hello World";

    laplace_lib_replace_char(str, 'd', 'a');
    cr_assert_str_eq(str, "Hello Worla");
}

Test(laplace_lib_replace_char_06, should_return_true)
{
    char str[] = "Hello World";

    laplace_lib_replace_char(str, ' ', 'a');
    cr_assert_str_eq(str, "HelloaWorld");
}

Test(laplace_lib_replace_char_07, should_return_true)
{
    char str[] = "Hello World";

    laplace_lib_replace_char(str, 'H', ' ');
    cr_assert_str_eq(str, " ello World");
}

Test(laplace_lib_replace_char_08, should_return_true)
{
    char str[] = "Hello World";

    laplace_lib_replace_char(str, 'W', ' ');
    cr_assert_str_eq(str, "Hello  orld");
}

Test(laplace_lib_replace_char_09, should_return_true)
{
    char *str = NULL;

    laplace_lib_replace_char(str, 'W', ' ');
    cr_assert_eq(str, NULL);
}

Test(laplace_lib_replace_char_10, should_return_true)
{
    char str[] = "Hello World";

    laplace_lib_replace_char(str, 'W', '\0');
    cr_assert_str_eq(str, "Hello ");
}

Test(laplace_lib_replace_char_11, should_return_true)
{
    char str[] = "Hello World";

    laplace_lib_replace_char(str, '\0', ' ');
    cr_assert_str_eq(str, "Hello World");
}

Test(laplace_lib_replace_char_12, should_return_true)
{
    char str[] = "Hello World";

    laplace_lib_replace_char(str, '\0', '\0');
    cr_assert_str_eq(str, "Hello World");
}

Test(laplace_lib_replace_char_13, should_return_true)
{
    char str[] = "";

    laplace_lib_replace_char(str, 'W', ' ');
    cr_assert_str_eq(str, "");
}
