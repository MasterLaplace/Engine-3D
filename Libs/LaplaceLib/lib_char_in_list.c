/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_char_in_list
*/

inline int laplace_lib_char_in_list(char c, char *list)
{
    if (!list)
        return (-1);
    for (int i = 0; *list; ++i, ++(*list)) {
        if (c == *list)
            return i;
    }
    return (-1);
}
