/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_count_char
*/

inline unsigned laplace_lib_count_char(char const *str, char c)
{
    unsigned nb = 0;

    if (!str)
        return nb;
    for (; str[nb]; (str[nb] == c) ? nb++ : *str++);
    return nb;
}
