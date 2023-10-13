/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** get_by_value
*/

#include "manager.h"

/**
 * @brief Get the by value object with only one attribute
 *
 * @param path  the path of the file
 * @param g_b_v  the structure of the function
 * @return char*  the value of the first attribute
 */
char *get_by_value(char *path, get_value_t g_b_v)
{
    char buffer[1024] = {0};
    char result[2048] = {0};
    FILE *fp;

    sprintf(buffer, GET_BY_VALUE, g_b_v.tag_name, g_b_v.attribute1);
    sprintf(result, GETTER_VALUE, buffer, g_b_v.attribute2, g_b_v.value, path);
    if (!(fp = popen(result, "r")))
        return (NULL);
    memset(result, 0, sizeof(result));
    fread(result, sizeof(char), sizeof(result), fp);
    pclose(fp);
    if (strlen(result) == 0)
        return (NULL);
    return strdup(result);
}

/**
 * @brief Get the by value object with two attributes
 *
 * @param tag_name  the tag name
 * @param attribute1  the first attribute
 * @param attribute2  the second attribute
 * @param value  the value of the second attribute
 * @return get_value_t  the structure of the function
 */
get_value_t init_get_by_value(char *tag_name, char *attribute1,
    char *attribute2, char *value)
{
    get_value_t g_b_v;

    g_b_v.tag_name = tag_name;
    g_b_v.attribute1 = attribute1;
    g_b_v.attribute2 = attribute2;
    g_b_v.value = value;
    return g_b_v;
}
