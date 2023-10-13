/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_getnbr_test
*/

#include <criterion/criterion.h>

unsigned laplace_lib_getnbr(char const *str);

Test(laplace_lib_getnbr_01, should_return_true)
{
    char *str = "Hello World";

    cr_assert_eq(laplace_lib_getnbr(str), 0);
}

Test(laplace_lib_getnbr_02, should_return_false)
{
    char *str = "Hello 150";

    cr_assert_eq(laplace_lib_getnbr(str), 0);
}

Test(laplace_lib_getnbr_03, should_return_false)
{
    char *str = "Hello -150";

    cr_assert_eq(laplace_lib_getnbr(str), 0);
}

Test(laplace_lib_getnbr_04, should_return_false)
{
    char *str = "150 World";

    cr_assert_eq(laplace_lib_getnbr(str), 150);
}

Test(laplace_lib_getnbr_05, should_return_false)
{
    char *str = "-150 World";

    cr_assert_eq(laplace_lib_getnbr(str), (-150));
}

Test(laplace_lib_getnbr_06, should_return_false)
{
    char *str = "Hello 150 World";

    cr_assert_eq(laplace_lib_getnbr(str), 0);
}

Test(laplace_lib_getnbr_07, should_return_false)
{
    char *str = "-150";

    cr_assert_eq(laplace_lib_getnbr(str), (-150));
}

Test(laplace_lib_getnbr_08, should_return_false)
{
    char *str = "150";

    cr_assert_eq(laplace_lib_getnbr(str), 150);
}

Test(laplace_lib_getnbr_09, should_return_false)
{
    char *str = NULL;

    cr_assert_eq(laplace_lib_getnbr(str), 0);
}

Test(laplace_lib_getnbr_10, should_return_false)
{
    char *str = "";

    cr_assert_eq(laplace_lib_getnbr(str), 0);
}
