/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_replace_char
*/

#ifdef __cplusplus
    #include <cstring>
#else
    #include <string.h>
#endif

inline void laplace_lib_replace_char(char *str, char orig, char rep)
{
    char *ix = str;

    if (!str || !*str || !orig)
        return;
    for (unsigned n = 0; (ix = strchr(ix, orig)); n++) {
        *ix++ = rep;
    }
}
