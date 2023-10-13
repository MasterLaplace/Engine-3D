/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_strcat
*/

#ifdef __cplusplus
    #include <cstring>
    #include <cstdlib>
#else
    #include <string.h>
    #include <stdlib.h>
#endif

inline char *laplace_lib_strcat(char const *dest, char const *src)
{
    char *tmp = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 1));
    unsigned i = 0;
    unsigned e = 0;

    if (!tmp)
        return (NULL);

    for (; src && src[i]; ++i)
        tmp[i] = src[i];
    for (; dest && dest[e]; ++i, ++e)
        tmp[i] = dest[e];
    tmp[i] = '\0';
    return tmp;
}
