#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include <threads.h>
#include <python3.9/Python.h>

int command_handler(void *);
char message[1000], server_response[1000];

static int send_recv(int client_socket) {
    // Sending a message to server
    if (send(client_socket, message, strlen(message), 0) < 0) {
        perror("Envoi du message au serveur échoué");
        exit(EXIT_FAILURE);
    }

    // Receiving response from server
    if (recv(client_socket, server_response, 1000, 0) < 0) {
        perror("Réception de la réponse du serveur échouée");
        exit(EXIT_FAILURE);
    }
    printf("Log: Réponse du serveur : %s\n", server_response);
    if (!strncmp(server_response, "exit", 4))
        return 1;
    memset(message, 0, 1000);
    memset(server_response, 0, 1000);
    return 0;
}

int main(int ac, char *av[]) {
    bool vocal = false;
    // Client connection
    int client_socket;
    struct sockaddr_in server_address;
    // Vocal command
    thrd_t thread;
    size_t size = 0;
    char *buf = NULL;
    char str[10];
    int fd[2];

    if (ac >= 2) {
        if (!strcmp(av[1], "-v"))
            vocal = true;
    }

    // Creating client socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Impossible de créer le socket client");
        return EXIT_FAILURE;
    }
    printf("Log: Socket client créé\n");

    // Configuration of server address | 192.168.31.163 |
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(49154);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connection to server
    if (connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Connexion au serveur échouée");
        return EXIT_FAILURE;
    }
    printf("Log: Connecté au serveur\n");

    if (vocal) {
        if (pipe(fd) == -1) {
            perror("Erreur dans la création du pipe");
            return EXIT_FAILURE;
        }

        sprintf(str, "%d", fd[1]);
        setenv("PIPE_FD", str, 1);

        if ( thrd_create( &thread, command_handler, NULL )) {
            perror("Impossible de créer le thread");
            return EXIT_FAILURE;
        }
        while (read(fd[0], message, 1000) > 0) {
            printf("Log: Message à envoyer au serveur : %s\n", message);
            if (send_recv(client_socket))
                break;
        }
    } else {
        while (1) {
            printf("Log: Message à envoyer au serveur : ");
            fgets(message, 1000, stdin);
            if (send_recv(client_socket))
                break;
        }
    }

    // Closing connection
    close(client_socket);
    return EXIT_SUCCESS;
}

int command_handler( void * Py_UNUSED(data) ) {
	char filename[] = "./src/client/vocal.py";
	FILE* fp;

	Py_Initialize();

	fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();
    return thrd_success;
}
