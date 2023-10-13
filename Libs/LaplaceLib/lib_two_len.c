/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_two_len
*/

inline unsigned laplace_lib_two_len(const char *tab[])
{
    unsigned i = 0;

    if (!tab)
        return i;

    for (; tab[i]; ++i);
    return i;
}
