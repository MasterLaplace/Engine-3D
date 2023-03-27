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
    #include <SFML/System/Vector3.h>

    #define Max_Port 0xFFFF
    #define Min_Port 0x0001
    #define ADDR svr->address
    #define SVR_SKT svr->server_socket
    #define FD_READ svr->readfds
    #define CLT_SKT(i) client[i].client_socket
    #define CLT_SOCK client->client_socket
    #define ADDR_LEN svr->addrlen
    #define UNUSED __attribute__((unused))
    #define auto __auto_type
    #define CODES_TYPE(i) codes[i].appId
    #define CODES_MSG(i) codes[i].msg
    #define MSG_SIZE(i) codes[i].size
    #define CODES(i) CODES_MSG(i), CODES_TYPE(i)

typedef struct sockaddr_in addr_in;
typedef struct sockaddr addr;
typedef unsigned int sizint;

typedef struct client_s {
    char *pseudo;
    bool connected;
    int client_socket;
    sfVector3f position;
} client_t;

typedef struct server_s {
    int server_socket;
    int addrlen;
    client_t client[SOMAXCONN];
    addr_in address;
    fd_set readfds;
    char *path;
    int port;
    size_t nbr_client;
} server_t;

typedef struct command_s {
    char *flag;
    void (*redirect)(client_t *client, char *buffer, server_t *svr);
} command_t;

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

bool print_help(char const *av[]);
bool set_server(server_t *svr);
bool loop(server_t *svr);
void manage(char *buffer, client_t *client, server_t *svr);

#endif /* !SERVER_H_ */
