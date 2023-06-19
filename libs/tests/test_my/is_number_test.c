/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** is_number_test
*/

#include <criterion/criterion.h>
#include <stdbool.h>

bool is_number(char const *str);

Test(is_number_01, should_return_false)
{
    char *str = "Hello World";

    cr_assert_eq(is_number(str), false);
}

Test(is_number_02, should_return_false)
{
    char *str = "Hello 150";

    cr_assert_eq(is_number(str), false);
}

Test(is_number_03, should_return_false)
{
    char *str = "Hello -150";

    cr_assert_eq(is_number(str), false);
}

Test(is_number_04, should_return_false)
{
    char *str = "150 World";

    cr_assert_eq(is_number(str), false);
}

Test(is_number_05, should_return_false)
{
    char *str = "-150 World";

    cr_assert_eq(is_number(str), false);
}

Test(is_number_06, should_return_false)
{
    char *str = "Hello 150 World";

    cr_assert_eq(is_number(str), false);
}

Test(is_number_07, should_return_true)
{
    char *str = "-150";

    cr_assert_eq(is_number(str), true);
}

Test(is_number_08, should_return_true)
{
    char *str = "150";

    cr_assert_eq(is_number(str), true);
}

Test(is_number_09, should_return_true)
{
    char *str = "0";

    cr_assert_eq(is_number(str), true);
}

Test(is_number_10, should_return_false)
{
    char *str = NULL;

    cr_assert_eq(is_number(str), false);
}

Test(is_number_11, should_return_false)
{
    char *str = "";

    cr_assert_eq(is_number(str), false);
}
