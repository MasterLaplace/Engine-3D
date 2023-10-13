/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** element
*/

#include "manager.h"

extern const format_t FORMATS[];

/**
 * @brief Add an element to a file
 *
 * @param files  The file to add the element to
 * @param path  The path of the file
 * @param type  The type of the element
 * @param ...  The arguments of the element
 */
void add_element(FILE **files, char *path, int type, ...)
{
    char line[1000];
    va_list args;
    va_start(args, type);
    char *av[FORMATS[type].nb_args];

    for (int i = 0; i < FORMATS[type].nb_args; i++)
        av[i] = va_arg(args, char *);
    while (fgets(line, sizeof(line), files[0]) != NULL) {
        if (strstr(line, FORMATS[type].close_tag_name) != NULL) {
            fprintf(files[1], FORMATS[type].tag_format, PRINTABLE(0),
                PRINTABLE(1), PRINTABLE(2), PRINTABLE(3), PRINTABLE(4));
            remove(path);
            rename("tmp.xml", path);
        }
        fprintf(files[1], "%s", line);
    }
    remove("tmp.xml");
    va_end(args);
}

/**
 * @brief Get the element object from a file
 *
 * @param path  The path of the file
 * @param tag_name  The name of the tag
 * @param attribute  The attribute of the tag (optional)
 * @return char*  The list of the elements: "element1\nelement2\n\0"
 */
char *get_element(char *path, char *tag_name, char *attribute)
{
    char buffer[1024] = {0};
    FILE *fp;

    if (!attribute)
        sprintf(buffer, GET_LIST, tag_name, tag_name, path);
    else
        sprintf(buffer, GET_LIST_ABUTE, tag_name, attribute, path);
    if (!(fp = popen(buffer, "r")))
        return (NULL);
    memset(buffer, 0, sizeof(buffer));
    fread(buffer, sizeof(char), sizeof(buffer), fp);
    pclose(fp);
    return strdup(buffer);
}

/**
 * @brief Get an attibute value following the uuid element from a file
 *
 * @param path  The path of the file
 * @param tag_name  The name of the tag
 * @param uuid  The uuid of the element
 * @param attribute  The attribute of the tag
 * @return char*  The element
 */
char *get_uuid_element(char *path, char *tag_name, char *uuid, char *attribute)
{
    char getter[1024] = {0};
    char result[2048] = {0};
    FILE *fp;

    sprintf(getter, GET_BY_UUID, tag_name, uuid, attribute);
    sprintf(result, GETTER, getter, path);
    if (!(fp = popen(result, "r")))
        return (NULL);
    memset(result, 0, sizeof(result));
    fread(result, sizeof(char), sizeof(result), fp);
    pclose(fp);
    return strdup(result);
}

/**
 * @brief Set an element in a file
 *
 * @param path  The path of the file
 * @param ele  The element to set
 */
void set_element(char *path, element_t ele)
{
    char modify[1024] = {0};
    char result[2048] = {0};
    FILE *fp;

    if (!ele.attribute && !ele.uuid) {
        sprintf(result, SET_LIST, ele.tag_name, ele.tag_name, ele.value, path);
    } else if (!ele.uuid) {
        sprintf(result, SET_LIST_ATTRIBUTE, ele.tag_name, ele.attribute);
        sprintf(modify, MODIFY, ele.attribute, ele.value, path);
        sprintf(result + strlen(result), "%s", modify);
    } else {
        sprintf(result, SET_BY_UUID, ele.tag_name, ele.uuid, ele.attribute);
        sprintf(modify, MODIFY_BY_UUID, ele.value, path);
        sprintf(result + strlen(result), "%s", modify);
    }
    if (!(fp = popen(result, "r")))
        return;
    pclose(fp);
}

/**
 * @brief Init an element
 *
 * @param tag_name  The name of the tag
 * @param attribute  The attribute of the tag (optional)
 * @param uuid  The uuid of the element (optional)
 * @param value  The new value of the element
 * @return element_t  The element
 */
element_t init_element(char *tag_nm, char *attribute, char *uuid, char *value)
{
    element_t ele;

    ele.tag_name = tag_nm;
    ele.attribute = attribute;
    ele.uuid = uuid;
    ele.value = value;
    return ele;
}
