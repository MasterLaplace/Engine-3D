/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** count_char_test
*/

#include <criterion/criterion.h>
#include <stddef.h>

unsigned count_char(char const *str, char c);

Test(count_char_01, should_return_true)
{
    char *str = "Hello World";
    char c = 'o';

    cr_assert_eq(count_char(str, c), 2);
}

Test(count_char_02, should_return_false)
{
    char *str = "Hello World";
    char c = 'a';

    cr_assert_eq(count_char(str, c), 0);
}

Test(count_char_03, should_return_false)
{
    char *str = "Hello World";
    char c = ' ';

    cr_assert_eq(count_char(str, c), 1);
}

Test(count_char_04, should_return_false)
{
    char *str = "Hello World";
    char c = '\0';

    cr_assert_eq(count_char(str, c), 0);
}

Test(count_char_05, should_return_false)
{
    char *str = "Hello World";
    char c = '\n';

    cr_assert_eq(count_char(str, c), 0);
}

Test(count_char_06, should_return_false)
{
    char *str = "Hello World";
    char c = '\t';

    cr_assert_eq(count_char(str, c), 0);
}

Test(count_char_07, should_return_false)
{
    char *str = "";
    char c = 'H';

    cr_assert_eq(count_char(str, c), 0);
}

Test(count_char_08, should_return_false)
{
    char *str = NULL;
    char c = 'H';

    cr_assert_eq(count_char(str, c), 0);
}

Test(count_char_09, should_return_false)
{
    char *str = "Hello World";
    char c = 'l';

    cr_assert_eq(count_char(str, c), 3);
}
