/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_getnbr
*/

#ifdef __cplusplus
    #include <cctype>
#else
    #include <ctype.h>
#endif

inline unsigned laplace_lib_getnbr(char const *str)
{
    unsigned exp = 0;

    if (!str)
        return exp;

    for (unsigned i = (*str == '-'); isdigit(str[i]); ++i)
        exp = exp * 10 + str[i] - '0';
    if ((*str == '-'))
        exp *= -1;
    return exp;
}
