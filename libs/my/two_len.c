/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** two_len
*/

unsigned two_len(const char *tab[])
{
    unsigned i = 0;

    if (!tab)
        return i;

    for (; tab[i]; ++i);
    return i;
}
