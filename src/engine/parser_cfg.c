/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** parser_obj
*/

#include "engine.h"

// yes Artisans_Hub.obj 1
config_t *init_config(char *buf)
{
    config_t *config = malloc(sizeof(config_t));
    char load[4] = {0};
    int collision = 0;

    sscanf(buf, "%s %s %d\n", load, config->name, &collision);
    config->load = !strcmp(load, "yes") ? true : false;
    config->collision = (uint8_t)collision;
    config->next = NULL;
    return config;
}

void add_config(char *buf)
{
    config_t *new = init_config(buf);
    config_t *tmp = engine.config;

    if (!tmp) {
        engine.config = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void free_config(config_t *config)
{
    config_t *tmp = config;

    while (tmp) {
        config = tmp->next;
        free(tmp);
        tmp = config;
    }
}

void parse_configs(void)
{
    char *buf = NULL;
    char **info = NULL;
    struct stat st;
    int fd = open_file("assets/config.cfg", O_RDONLY);

    if (fd == -1)
        return;
    stat("assets/config.cfg", &st);
    if (!(buf = malloc(sizeof(char) * (st.st_size + 1))))
        return;
    if (read(fd, buf, st.st_size) == -1)
        return;
    buf[st.st_size] = '\0';
    info = stwa(buf, "\n");
    for (sizint i = 0; info[i]; i++) {
        if (info[i][0] == '#')
            continue;
        add_config(info[i]);
    }
    free(buf);
    two_free(info);
    close(fd);
}
