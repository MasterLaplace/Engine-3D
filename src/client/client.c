/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** client
*/

#include "client.h"

int command_handler(void *);
char message[1000], server_response[1000];

static int send_recv(int client_socket)
{
    if (send(client_socket, message, strlen(message), 0) < 0) {
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (recv(client_socket, server_response, 1000, 0) < 0) {
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("Log: Réponse du serveur : %s\n", server_response);
    if (!strncmp(server_response, "exit", 4))
        return 1;
    memset(message, 0, 1000);
    memset(server_response, 0, 1000);
    return 0;
}


bool set_server(server_t *svr)
{
    if ((svr->client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror(strerror(errno));
        return false;
    }

    ADDR.sin_family = AF_INET;
    ADDR.sin_port = htons(49154);
    ADDR.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(svr->client_socket, (addr *) &ADDR, sizeof(ADDR)) < 0) {
        perror(strerror(errno));
        return false;
    }
    return true;
}

void set_vocal(server_t *svr)
{
    thrd_t thread;
    size_t size = 0;
    char *buf = NULL;
    char str[10];
    int fd[2];

    if (pipe(fd) == -1) {
        perror(strerror(errno));
        return;
    }

    sprintf(str, "%d", fd[1]);
    setenv("PIPE_FD", str, 1);

    if ( thrd_create( &thread, command_handler, NULL )) {
        perror(strerror(errno));
        return;
    }
    while (read(fd[0], message, 1000) > 0) {
        printf("Log: Message à envoyer au serveur : %s\n", message);
        if (send_recv(svr->client_socket))
            break;
    }
}

void loop(server_t *svr)
{
    while (1) {
        printf("Log: Message à envoyer au serveur : ");
        fgets(message, 1000, stdin);
        if (send_recv(svr->client_socket))
            break;
    }
}

int main(int ac, char *av[])
{
    bool vocal = false;
    server_t svr;
    int client_socket;

    if (ac >= 2) {
        if (!strcmp(av[1], "-v"))
            vocal = true;
    }

    if (!set_server(&svr))
        return EXIT_FAILURE;

    if (vocal)
        set_vocal(&svr);
    else
        loop(&svr);

    close(client_socket);
    return EXIT_SUCCESS;
}

int command_handler( void * data __attribute__((unused)) ) {
    system("python3 ./src/client/vocal.py");
    return thrd_success;
}
