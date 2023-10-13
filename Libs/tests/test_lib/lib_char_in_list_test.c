/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_char_in_list_test
*/

#include <criterion/criterion.h>

int laplace_lib_char_in_list(char c, char *list);

Test(laplace_lib_char_in_list_01, should_return_true)
{
    char a = 'H';
    char *list = "Hello";

    cr_assert_neq(laplace_lib_char_in_list(a, list), (-1));
}

Test(laplace_lib_char_in_list_02, should_return_false)
{
    char a = 'H';
    char *list = "World";

    cr_assert_eq(laplace_lib_char_in_list(a, list), (-1));
}

Test(laplace_lib_char_in_list_03, should_return_false)
{
    char a = 'H';
    char *list = "";

    cr_assert_eq(laplace_lib_char_in_list(a, list), (-1));
}

Test(laplace_lib_char_in_list_04, should_return_false)
{
    char a = 'H';
    char *list = NULL;

    cr_assert_eq(laplace_lib_char_in_list(a, list), (-1));
}
