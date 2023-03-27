/*
** ME PROJECT, 2022
** B-SYN-200-REN-2-1-sbmlparser-guillaume.papineau
** File description:
** my_stwa
*/

#include "my.h"

static size_t count_words(char *str, const char *delim)
{
    char *str_dup = NULL;
    size_t count = 0;

    if (!str)
        return (0);
    str_dup = strdup(str);
    if (strtok(str_dup, delim))
        count++;
    while (strtok(NULL, delim))
        count++;
    free(str_dup);
    return count;
}

char **stwa(char *str, const char *delim)
{
    size_t len = count_words(str, delim);
    char **words = malloc(sizeof(char *) * (len + 1));
    char *str_dup = NULL;

    if (len == 0) {
        free(words);
        return (NULL);
    }
    str_dup = strdup(str);
    words[0] = strdup(strtok(str_dup, delim));
    for (size_t i = 1; i < len; ++i)
        words[i] = strdup(strtok(NULL, delim));
    words[len] = NULL;
    free(str_dup);
    return words;
}
