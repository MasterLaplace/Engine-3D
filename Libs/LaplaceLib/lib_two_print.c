/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_two_print
*/

#ifdef __cplusplus
    #include <cstdio>
#else
    #include <stdio.h>
#endif

inline void laplace_lib_two_print(const char *tab[])
{
    if (!tab)
        return;
    for (; *tab; ++tab)
        printf("%s\n", *tab);
}
