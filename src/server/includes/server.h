/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/time.h>
    #include <stdbool.h>

    #define Max_Port 0x0000FFFF
    #define Min_Port 0x0
    #define ADDR svr->address

typedef struct sockaddr_in addr_in;
typedef struct sockaddr addr;
typedef unsigned int sizint;

typedef enum {
    Server_GetStatus,
    Server_GetPing,

    Client_Accepted,
    Client_AssignID,
    Client_RegisterWithServer,
    Client_UnregisterWithServer,

    Game_AddPlayer,
    Game_RemovePlayer,
    Game_UpdatePlayer
} command;

typedef struct client_s {
    char *pseudo;
    char *password;
} client_t;

typedef struct server_s {
	int server_socket;
    int addrlen;
    int client_socket[SOMAXCONN];
    int sd;
	addr_in address;
	fd_set readfds;
} server_t;

bool print_help(char const *av[]);
bool set_server(server_t *svr, int port);
bool loop(server_t *svr);

#endif /* !SERVER_H_ */
