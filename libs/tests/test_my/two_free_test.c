/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** two_free_test
*/

#include <criterion/criterion.h>
#include <stdlib.h>

void two_free(char **tab);

Test(two_free_01, should_free_tab)
{
    char **tab = malloc(sizeof(char *) * 2);

    tab[0] = malloc(sizeof(char) * 2);
    tab[1] = malloc(sizeof(char) * 2);
    tab[0][0] = 'a';
    tab[0][1] = '\0';
    tab[1][0] = 'b';
    tab[1][1] = '\0';
    two_free(tab);
    cr_assert_not_null(tab[0]);
    cr_assert_not_null(tab[1]);
}

Test(two_free_02, should_free_tab)
{
    char **tab = NULL;

    two_free(tab);
    cr_assert_eq(tab, NULL);
}

Test(two_free_03, should_free_tab)
{
    char **tab = malloc(sizeof(char *) * 2);

    tab[0] = NULL;
    tab[1] = NULL;
    two_free(tab);
    cr_assert_not_null(tab[0]);
    cr_assert_not_null(tab[1]);
}
