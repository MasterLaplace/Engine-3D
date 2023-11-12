/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_two_free_test
*/

#include <criterion/criterion.h>

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

void laplace_lib_two_free(char **tab);

Test(laplace_lib_two_free_01, should_free_tab)
{
    char **tab = malloc(sizeof(char *) << 1);

    tab[0] = malloc(sizeof(char) << 1);
    tab[1] = malloc(sizeof(char) << 1);
    tab[0][0] = 'a';
    tab[0][1] = '\0';
    tab[1][0] = 'b';
    tab[1][1] = '\0';
    laplace_lib_two_free(tab);
    cr_assert_not_null(tab[0]);
    cr_assert_not_null(tab[1]);
}

Test(laplace_lib_two_free_02, should_free_tab)
{
    char **tab = NULL;

    laplace_lib_two_free(tab);
    cr_assert_eq(tab, NULL);
}

Test(laplace_lib_two_free_03, should_free_tab)
{
    char **tab = malloc(sizeof(char *) << 1);

    tab[0] = NULL;
    tab[1] = NULL;
    laplace_lib_two_free(tab);
    cr_assert_not_null(tab[0]);
    cr_assert_not_null(tab[1]);
}
