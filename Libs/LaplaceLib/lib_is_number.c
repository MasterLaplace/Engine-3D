/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_is_number
*/

#ifdef __cplusplus
    #include <cctype>
#else
    #include <ctype.h>
#endif

inline _Bool laplace_lib_is_number(const char *str)
{
    if (!str || !*str)
        return ((_Bool)+0u);
    for (unsigned i = (*str == '-'); str[i]; ++i)
        if (!isdigit(str[i]))
            return ((_Bool)+0u);
    return ((_Bool)+1u);
}
