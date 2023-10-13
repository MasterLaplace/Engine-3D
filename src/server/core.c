/*
** EPITECH PROJECT, 2023
** Engine-3D
** File description:
** Daemon 0.1
*/

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <sys/time.h>
// #include <stdbool.h>
// #include "lib.h"
// #include "link_list.h"

// #include <stdlib.h>
// #include <unistd.h>
// #define ATTR(key) __attribute__((key))
// #define ON_CLEANUP(func) ATTR(cleanup(func))
// #define AUTO_FREE ON_CLEANUP(free_stack)
// #define ALWAYS_INLINE ATTR(always_inline)
// #define IS_USED_BY_AUTO_CLEANUP(var) (void)(var)
// #define NEED_COMMA struct _
// #define STA_INL static inline ALWAYS_INLINE
// #define CLF_HEAD(name, ptr) STA_INL void name(void *ptr)
// #define CLF_BODY(type, func, ptr) if (*(type *)(ptr)) func(*(type *)ptr);
// #define CL_INTERN(n, t, f) CLF_HEAD(n, ptr) { CLF_BODY(t, f, ptr) }
// #define CLEANUP_FUNC(n, t, f) CL_INTERN(n, t, f) NEED_COMMA

// CLEANUP_FUNC(free_stack, void *, free);



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "lib.h"
#include "link_list.h"

#define MAX_CLIENTS SOMAXCONN
#define BUFFER_SIZE 1024

int main() {
    int sockfd, newsockfd, maxfd, activity, i, valread, sd;
    int client_sockets[MAX_CLIENTS];
    fd_set readfds;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr;

    // Initialisation du tableau des sockets clients
    for (i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = 0;
    }

    // Création du socket principal
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8888);

    // Attache du socket à l'adresse du serveur
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erreur lors de la liaison");
        exit(EXIT_FAILURE);
    }

    // Mise en mode d'écoute
    if (listen(sockfd, 5) < 0) {
        perror("Erreur lors de l'écoute");
        exit(EXIT_FAILURE);
    }

    printf("Serveur en attente de connexions...\n");

    // Boucle principale du serveur
    while (1) {
        FD_ZERO(&readfds);

        // Ajout du socket principal à l'ensemble des descripteurs surveillés
        FD_SET(sockfd, &readfds);
        maxfd = sockfd;

        // Ajout des sockets clients à l'ensemble des descripteurs surveillés
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];

            if (sd > 0)
                FD_SET(sd, &readfds);

            if (sd > maxfd)
                maxfd = sd;
        }

        // Attente d'une activité sur l'un des descripteurs surveillés
        activity = select(maxfd + 1, &readfds, NULL, NULL, NULL);

        if (activity < 0) {
            perror("Erreur lors de l'appel à select");
            exit(EXIT_FAILURE);
        }

        // Si une activité est détectée sur le socket principal, c'est une nouvelle connexion
        if (FD_ISSET(sockfd, &readfds)) {
            if ((newsockfd = accept(sockfd, (struct sockaddr *)NULL, NULL)) < 0) {
                perror("Erreur lors de l'acceptation de la connexion");
                exit(EXIT_FAILURE);
            }

            printf("Nouvelle connexion acceptée. Socket descripteur : %d\n", newsockfd);

            // Ajout du nouveau socket client au tableau
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = newsockfd;
                    break;
                }
            }
        }

        // Vérification des autres sockets (sockets clients) pour la lecture
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];

            if (FD_ISSET(sd, &readfds)) {
                // Lecture du message reçu
                if ((valread = read(sd, buffer, BUFFER_SIZE)) == 0) {
                    // Connexion fermée par le client
                    getpeername(sd, (struct sockaddr *)&serv_addr, (socklen_t *)&addrlen);
                    printf("Client déconnecté. Socket descripteur : %d, IP : %s, Port : %d\n", sd, inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));

                    // Fermeture du socket client et suppression du descripteur du tableau
                    close(sd);
                    client_sockets[i] = 0;
                } else {
                    // Affichage du message reçu
                    buffer[valread] = '\0';
                    printf("Message reçu du client %d : %s\n", sd, buffer);

                    // Envoyer une réponse au client
                    send(sd, "Message reçu par le serveur.", strlen("Message reçu par le serveur."), 0);
                }
            }
        }
    }

    return 0;
}
