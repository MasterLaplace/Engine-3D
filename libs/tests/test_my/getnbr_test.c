/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** getnbr_test
*/

#include <criterion/criterion.h>

unsigned getnbr(char const *str);

Test(getnbr_01, should_return_true)
{
    char *str = "Hello World";

    cr_assert_eq(getnbr(str), 0);
}

Test(getnbr_02, should_return_false)
{
    char *str = "Hello 150";

    cr_assert_eq(getnbr(str), 0);
}

Test(getnbr_03, should_return_false)
{
    char *str = "Hello -150";

    cr_assert_eq(getnbr(str), 0);
}

Test(getnbr_04, should_return_false)
{
    char *str = "150 World";

    cr_assert_eq(getnbr(str), 150);
}

Test(getnbr_05, should_return_false)
{
    char *str = "-150 World";

    cr_assert_eq(getnbr(str), (-150));
}

Test(getnbr_06, should_return_false)
{
    char *str = "Hello 150 World";

    cr_assert_eq(getnbr(str), 0);
}

Test(getnbr_07, should_return_false)
{
    char *str = "-150";

    cr_assert_eq(getnbr(str), (-150));
}

Test(getnbr_08, should_return_false)
{
    char *str = "150";

    cr_assert_eq(getnbr(str), 150);
}

Test(getnbr_09, should_return_false)
{
    char *str = NULL;

    cr_assert_eq(getnbr(str), 0);
}

Test(getnbr_10, should_return_false)
{
    char *str = "";

    cr_assert_eq(getnbr(str), 0);
}
