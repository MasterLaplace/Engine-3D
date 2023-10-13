/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_stwa
*/

#ifdef __cplusplus
    #include <cstring>
    #include <cstdlib>
#else
    #include <string.h>
    #include <stdlib.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define strdup(__s) _strdup(__s)
#endif

static unsigned laplace_lib_count_words(char *str, const char *delim)
{
    char *str_dup = NULL;
    unsigned count = 0;

    if (!str)
        return (0);
    str_dup = strdup(str);
    if (strtok(str_dup, delim))
        count++;
    for (; strtok(NULL, delim); count++);
    free(str_dup);
    return count;
}

char **laplace_lib_stwa(char *str, const char *delim)
{
    unsigned len = laplace_lib_count_words(str, delim);
    char **words = malloc(sizeof(char *) * (len + 1));
    char *str_dup = NULL;

    if (len == 0) {
        free(words);
        return (NULL);
    }
    str_dup = strdup(str);
    words[0] = strdup(strtok(str_dup, delim));
    for (unsigned i = 1; i < len; ++i)
        words[i] = strdup(strtok(NULL, delim));
    words[len] = NULL;
    free(str_dup);
    return words;
}
