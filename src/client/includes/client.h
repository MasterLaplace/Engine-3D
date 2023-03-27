/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myftp-guillaume.papineau
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_
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
    #include <threads.h>
    #include <python3.9/Python.h>

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
} command_t;

typedef struct client_s {
    char *pseudo;
    char *password;
} client_t;

typedef struct server_s {
    int client_socket;
	addr_in address;
} server_t;

bool set_server(server_t *svr);

#endif /* !CLIENT_H_ */
