/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** is_null_link
*/

#include "linkList.h"

bool is_null_link(link_t **link)
{
    if (!link || !*link)
        return true;
    else
        return false;
}
