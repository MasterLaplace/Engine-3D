/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** check_endian_test
*/

#include <criterion/criterion.h>

int check_endianness(void);

Test(check_endian_01, should_return_true)
{
    cr_assert_eq(check_endianness(), 1);
}

Test(check_endian_02, should_return_false)
{
    cr_assert_neq(check_endianness(), 0);
}
