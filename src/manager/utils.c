/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** utils
*/

#include "manager.h"

/**
 * @brief Get the file size object
 * Use fseek and ftell to check if the file is empty
 * @param file  The file to check
 * @return long  The size of the file
 */
long get_file_size(FILE *file)
{
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

/**
 * @brief Create a unique file object
 *
 * @param type  The type of the file (TEAM_TYPE, CHANNEL_TYPE, THREAD_TYPE)
 * @param uuid  The uuid of the object
 * @return char*  The path of the file
 */
char *create_unique_file(char *type, char *uuid)
{
    char command[strlen(DATA_PATH) + strlen(type) + strlen(uuid) + 30];
    FILE *file;

    snprintf(command, sizeof(command), "mkdir -p %s%s", DATA_PATH, type);
    system(command);
    snprintf(command, sizeof(command), "%s%s%s.xml", DATA_PATH, type, uuid);

    if (access(command, F_OK) == 0)
        return NULL;
    if (!(file = fopen(command, "w")))
        return NULL;
    fclose(file);

    char *path = malloc(strlen(DATA_PATH) + strlen(type) + strlen(uuid) + 5);

    sprintf(path, "%s%s%s.xml", DATA_PATH, type, uuid);
    return path;
}

char *create_path_file(char *type, char *uuid)
{
    char *path = malloc(strlen(DATA_PATH) + strlen(type) + strlen(uuid) + 5);

    sprintf(path, "%s%s%s.xml", DATA_PATH, type, uuid);
    return path;
}
