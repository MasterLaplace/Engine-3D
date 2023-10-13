/*
** EPITECH PROJECT, 2023
** Title: Laplace Lib Library v1.0.0
** Author: MasterLaplace
** Created: 2023-10-13
** File description:
** lib_check_endian
*/

inline int laplace_lib_check_endianness(void)
{
    unsigned x = 1;
    char *c = (char*) &x;

    return (int)*c;
}
