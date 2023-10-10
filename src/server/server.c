/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myftp-guillaume.papineau
** File description:
** Daemon 0.1
*/

#include "server.h"
#include <signal.h>
#include <ctype.h>


static void unknown(client_t *client, char *buffer UNUSED)
{
    write(CLT_SOCK, "500 Unknown command.\r\n", 23);
}

static void get_pos(client_t *client, char *buffer UNUSED, server_t *svr UNUSED)
{
    auto pos = strtok(NULL, " \r");

    if (!pos) {
        write(CLT_SOCK, "500 Unknown command.\r\n", 23);
        return;
    }

    printf("LOG: %f %f %f", client->position.x, client->position.y, client->position.z);
    dprintf(CLT_SOCK, "201 %s %f %f %f\r\n", client->pseudo, client->position.x, client->position.y, client->position.z);
}

static void set_pos(client_t *client, char *buffer UNUSED, server_t *svr UNUSED)
{
    auto pos = strtok(NULL, " \r");

    if (!pos) {
        write(CLT_SOCK, "500 Unknown command.\r\n", 23);
        return;
    }

    client->position.x = atof(pos);
    pos = strtok(NULL, " \r");
    client->position.y = atof(pos);
    pos = strtok(NULL, " \r");
    client->position.z = atof(pos);
    printf("LOG: %f %f %f", client->position.x, client->position.y, client->position.z);
    write(CLT_SOCK, "200 OK\r\n", 9);
}

static void set_pseudo(client_t *client, char *buffer UNUSED, server_t *svr UNUSED)
{
    auto pseudo = strtok(NULL, " \r");

    if (!pseudo) {
        write(CLT_SOCK, "500 Unknown command.\r\n", 23);
        return;
    }

    strcpy(client->pseudo, pseudo);
    write(CLT_SOCK, "200 OK\r\n", 9);
}

static void get_nbr(client_t *client, char *buffer UNUSED, server_t *svr)
{
    auto nbr = strtok(NULL, " \r");

    if (!nbr) {
        write(CLT_SOCK, "500 Unknown command.\r\n", 23);
        return;
    }

    dprintf(CLT_SOCK, "201 %ld\r\n", svr->nbr_client);
}

const command_t commands[] = {
    {"GET_POS", &get_pos},
    {"SET_POS", &set_pos},
    {"SET_PSEUDO", &set_pseudo},
    {"GET_NBR", &get_nbr},
    {NULL, NULL}
};

void manage(char *buffer, client_t *client, server_t *svr)
{
    auto command = strtok(buffer, " \r");

    for (size_t i = 0; commands[i].flag; i++) {
        if (!strcmp(command, commands[i].flag)) {
            commands[i].redirect(client, buffer, svr);
            return;
        }
    }

    unknown(client, buffer);
}

static void set_sock(server_t *svr)
{
    if (setsockopt(SVR_SKT, SOL_SOCKET, SO_REUSEADDR, "\001", 4) < 0 )
        perror(strerror(errno));
}

bool set_server(server_t *svr)
{
    memset(svr->client, 0, sizeof(svr->client));
    if ((SVR_SKT = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror(strerror(errno));
        return false;
    }
    set_sock(svr);
    ADDR.sin_family = AF_INET;
    ADDR.sin_addr.s_addr = INADDR_ANY;
    ADDR.sin_port = htons(svr->port);
    if (bind(SVR_SKT, (addr *)&ADDR, sizeof(ADDR)) < 0) {
        perror(strerror(errno));
        return false;
    }
    if (listen(SVR_SKT, 3) < 0) {
        perror(strerror(errno));
        return false;
    }
    ADDR_LEN = sizeof(ADDR);
    return true;
}

static void read_data_from_server(server_t *svr)
{
    char buffer[1025];

    for (sizint i = 0; i < SOMAXCONN; i++) {
        auto sd = svr->CLT_SKT(i);
        int valread;

        if (!FD_ISSET( sd, &FD_READ))
            continue;
        if ((valread = read(sd, buffer, 1024)) == 0) {
            getpeername(sd, (addr*)&ADDR, (socklen_t*)&ADDR_LEN);
            close(sd);
            svr->CLT_SKT(i) = 0;
        } else {
            buffer[valread] = '\0';
            manage(buffer, &svr->client[i], svr);
        }
    }
}

static void handle_new_connection(server_t *svr)
{
    auto message = "version: Daemon 0.1\r\n";
    int new_skt;

    if (!FD_ISSET(SVR_SKT, &FD_READ))
        return;
    if ((new_skt = accept(SVR_SKT, (addr *)&ADDR, (socklen_t*)&ADDR_LEN)) < 0) {
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (write(new_skt, message, strlen(message)) < 0) {
        perror(strerror(errno));
    }
    for (sizint i = 0; i < SOMAXCONN; i++) {
        if (svr->CLT_SKT(i) == 0) {
            svr->CLT_SKT(i) = new_skt;
            svr->nbr_client++;
            break;
        }
    }
}

static int set_fd(server_t *svr)
{
    FD_ZERO(&FD_READ);
    FD_SET(SVR_SKT, &FD_READ);
    int max_sd = SVR_SKT;

    for (sizint i = 0; i < SOMAXCONN; i++) {
        int sd = svr->CLT_SKT(i);

        if (sd > 0)
            FD_SET(sd, &FD_READ);

        if (sd > max_sd)
            max_sd = sd;
    }
    return max_sd;
}

static void check_actions(server_t *svr)
{
    auto activity = select( set_fd(svr) + 1, &FD_READ, NULL, NULL, NULL);
    if ((activity < 0) && (errno != EINTR)) {
        perror(strerror(errno));
    }
}

bool loop(server_t *svr)
{
    while (true) {
        check_actions(svr);
        handle_new_connection(svr);
        read_data_from_server(svr);
    }
    return true;
}

static bool is_number(const char *str)
{
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}

static const char *help_msg[] = {
    "USAGE: ./myftp port",
    "\tport is the port number on which the server socket listens",
    NULL
};

static bool help(char const *av[])
{
    if (strcmp(av[1], "-h") && strcmp(av[1], "-help"))
        return false;
    two_put(help_msg);
    return true;
}

int main(int ac , const char *av[])
{
    server_t svr;

    if (ac < 2)
        return 84;
    if (help(av))
        return 0;
    if (!is_number(av[1]))
        return 84;
    svr.port = atoi(av[1]);
    if (svr.port > Max_Port || svr.port < Min_Port)
        return 84;
    if (!set_server(&svr))
        return 84;
    if (!loop(&svr))
        return 84;
    return 0;
}
