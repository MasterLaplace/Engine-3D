/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_two_len_test
*/

#include <criterion/criterion.h>

unsigned laplace_lib_two_len(const char *tab[]);

Test(laplace_lib_two_len_01, should_return_true)
{
    const char *tab[] = {"Hello", "World", NULL};

    cr_assert_eq(laplace_lib_two_len(tab), 2);
}

Test(laplace_lib_two_len_02, should_return_false)
{
    const char *tab[] = {"Hello", "World", "!", NULL};

    cr_assert_eq(laplace_lib_two_len(tab), 3);
}

Test(laplace_lib_two_len_03, should_return_false)
{
    const char *tab[] = {"Hello", NULL};

    cr_assert_eq(laplace_lib_two_len(tab), 1);
}

Test(laplace_lib_two_len_04, should_return_false)
{
    const char *tab[] = {NULL};

    cr_assert_eq(laplace_lib_two_len(tab), 0);
}

Test(laplace_lib_two_len_05, should_return_false)
{
    const char *tab[] = {"Hello", "World", "!", "!", NULL};

    cr_assert_eq(laplace_lib_two_len(tab), 4);
}
