#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void *connection_handler(void *);

int nbr_connection = 0;

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    int address_length = sizeof(client_address);
    pthread_t sniffer_thread;

    fd_set set_timeout;
    struct timeval timeout;
    timeout.tv_sec = 15;
    timeout.tv_usec = 0;

    // Creation of server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Impossible de créer le socket serveur");
        return EXIT_FAILURE;
    }
    printf("Log: Socket serveur créé\n");

    // Configuration of server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(49154);

    // Binding socket server to address
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Liaison du socket serveur à une adresse échouée");
        return EXIT_FAILURE;
    }
    printf("Log: Socket serveur lié à une adresse\n");

    // Listening for incoming connections
    listen(server_socket, 3);
    printf("Log: En attente de connexions entrantes...\n");

    while (1) {
        // restart timeout and add file descriptor to the set_timeout
        FD_ZERO(&set_timeout);
        FD_SET(server_socket, &set_timeout);

        if (!select(server_socket + 1, &set_timeout, NULL, NULL, &timeout) && nbr_connection == 0) {
            printf("Log: Timeout dépassé\n");
            break;
        }

        // Accepting an incoming connection
        if ((client_socket = accept(server_socket, (struct sockaddr *) &client_address, &address_length)) < 0) {
            perror("Acceptation d'une connexion entrante échouée");
            return EXIT_FAILURE;
        }
        printf("Log: Connexion entrante acceptée\n");

        // Creation of a new thread to manage the incoming connection
        if (pthread_create(&sniffer_thread, NULL, connection_handler, &client_socket) < 0) {
            perror("Création du thread pour gérer la connexion entrante échouée");
            return EXIT_FAILURE;
        }
        printf("Log: Thread pour gérer la connexion entrante créé\n");
    }

    return EXIT_SUCCESS;
}

void *connection_handler(void *socket_desc) {
    int client_socket = *(int*)socket_desc;
    char client_message[1000];
    int read_size;

    nbr_connection++;

    while (1) {
        // Receiving message from client
        while((read_size = recv(client_socket, client_message, 1000, 0)) > 0) {
            // Sending message to client
            write(client_socket, client_message, strlen(client_message));

            if (!strncmp(client_message, "exit", 4))
                goto exit;
            memset(client_message, 0, 1000);
        }
    }

exit:
    // Closing connection with client
    printf("Log: Connexion client terminée\n");
    close(client_socket);
    nbr_connection--;
    return 0;
}
