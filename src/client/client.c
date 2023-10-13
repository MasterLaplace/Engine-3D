/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** Steinhauer 0.1
*/

#include "client.h"
#include "engine.h"

engine_t engine;

int command_handler(void *);
char message[1000], server_response[1000];

static int send_recv(int client_socket)
{
    printf("LOG: %s\n", message);
    if (!strncmp(message, "avance", 6)) {
        engine.Pos.x += 100;
        printf("LOG: %f\n", engine.Pos.x);
    }
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
    ADDR.sin_port = htons(4242);
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

void init(void) __attribute__((constructor));
void clean(void) __attribute__((destructor));

void init(void)
{
    if (!open_folder( "./assets/obj_examples/" ))
        exit(EXIT_FAILURE);
    if (!init_engine())
        exit(EXIT_FAILURE);
}

void clean(void)
{
    destroying();
}

int loop_client(void *data)
{
    server_t svr;

    if (!set_server(&svr))
        return 1;
    if ((bool) data)
        set_vocal(&svr);
    else
        loop(&svr);
    close(svr.client_socket);
    return 0;
}

int main(int ac, char *av[])
{
    thrd_t thread;
    bool vocal = false;

    if (ac >= 2) {
        if (!strcmp(av[1], "-v"))
            vocal = true;
    }

    if ( thrd_create( &thread, &loop_client, (void *) vocal )) {
        perror(strerror(errno));
        return EXIT_FAILURE;
    }

    loop_engine();

    return EXIT_SUCCESS;
}

int command_handler( void * Py_UNUSED(data) ) {
    static const char filename[] = "./src/client/vocal.py";
	FILE* fp;

	Py_Initialize();

	fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();
    return thrd_success;
}
