/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_check_endian_test
*/

#include <criterion/criterion.h>

int laplace_lib_check_endianness(void);

Test(check_endian_01, should_return_true)
{
    cr_assert_eq(laplace_lib_check_endianness(), 1);
}

Test(check_endian_02, should_return_false)
{
    cr_assert_neq(laplace_lib_check_endianness(), 0);
}
