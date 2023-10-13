/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_two_print_test
*/

#include <criterion/criterion.h>

void laplace_lib_two_print(const char *tab[]);

Test(laplace_lib_two_print_01, should_print_tab)
{
    const char *tab[] = {"Hello", "World", NULL};

    laplace_lib_two_print(tab);
    cr_assert_eq(0, 0);
}

Test(laplace_lib_two_print_02,  should_not_crash)
{
    const char *tab[] = {NULL};

    laplace_lib_two_print(tab);
    cr_assert_eq(0, 0);
}
