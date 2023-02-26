/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myftp-guillaume.papineau
** File description:
** server
*/

#include "server.h"

bool set_server(server_t *svr, int port)
{
	if( (svr->server_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) {
		perror(strerror(errno));
		return false;
	}
	ADDR.sin_family = AF_INET;
	ADDR.sin_addr.s_addr = INADDR_ANY;
	ADDR.sin_port = htons(port);

	if (bind(svr->server_socket, (addr *)&(ADDR), sizeof(ADDR)) < 0) {
		perror(strerror(errno));
		return false;
	}
	if (listen(svr->server_socket, SOMAXCONN) < 0) {
		perror(strerror(errno));
		return false;
	}
    memset(svr->client_socket, 0, sizeof(svr->client_socket));
	svr->addrlen = sizeof(ADDR);
    return true;
}

static void set_select(server_t *svr)
{
    FD_ZERO(&svr->readfds);
    FD_SET(svr->server_socket, &svr->readfds);

    for (sizint i = 0; i < SOMAXCONN; i++) {
        svr->sd = svr->client_socket[i];

        if(svr->sd > 0)
            FD_SET(svr->sd, &(svr->readfds));

        if(svr->sd > svr->server_socket)
            svr->server_socket = svr->sd;
    }
}

static bool check_action(server_t *svr)
{
	char *message = "Laplace v1.0\r\n";
    int new_socket = 0;

    if (!FD_ISSET(svr->server_socket, &(svr->readfds)))
        return false;
    if ((new_socket = accept(svr->server_socket, (addr *)&(ADDR),
        (socklen_t*)&(svr->addrlen))) < 0) {
        perror(strerror(errno));
        return false;
    }
    write(new_socket, message, strlen(message));
    for (sizint i = 0; i < SOMAXCONN; i++) {
        if(svr->client_socket[i] == 0) {
            svr->client_socket[i] = new_socket;
            break;
        }
    }
    return true;
}

static void send_recv(server_t *svr)
{
    char buffer[1025];
    int valread = 0;

    for (sizint i = 0; i < SOMAXCONN; i++) {
        svr->sd = svr->client_socket[i];
            
        if (!FD_ISSET(svr->sd, &(svr->readfds)))
            continue;
        if ((valread = read(svr->sd, buffer, 1024)) == 0) {
            close(svr->sd);
            svr->client_socket[i] = 0;
        } else {
            buffer[valread] = '\0';
            write(svr->sd, buffer, strlen(buffer));
        }
    }
}

bool loop(server_t *svr)
{
    int activity = 0;

    while(true) {
        set_select(svr);

		activity = select(svr->server_socket + 1, &(svr->readfds), NULL, NULL, NULL);

		if ((activity < 0) && (errno != EINTR))
			perror(strerror(errno));
		if (!check_action(svr))
            return false;
		send_recv(svr);
	}
    close(svr->server_socket);
    return true;
}

/* HELP */

static const char *help[] = {
    "USAGE: ./myftp port path",
    "\tport is the port number on which the server socket listens",
    NULL
};

static void two_put(char **tab)
{
    for (; tab && *tab; tab++)
        printf("%s\n", *tab);
}


bool print_help(char const *av[])
{
    if (strcmp(av[1], "-h") && strcmp(av[1], "-help"))
        return false;
    two_put((char **) help);
    return true;
}

int main(int ac , const char *av[])
{
    server_t svr;
    int port = 0;

    if (ac < 2)
        return 84;

    if (print_help(av))
        return 0;

    if ((port = atoi(av[1])) > Max_Port || port < Min_Port)
        return 84;

	if (!set_server(&svr, port))
        return 84;

    if (!loop(&svr))
        return 84;
	return 0;
}
