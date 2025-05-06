#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "client_handler.h"

struct sockaddr_in server_addr;

int main(int argc, char **argv) {
    // Create socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("socket creation failed");
        exit(1);
    }

    // Socket address config

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind socket
    if (bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
        0) {
        perror("bind failed");
        exit(1);
    }

    // Listen for connections
    if (listen(server, 5) < 0) {
        perror("listen failed");
        exit(1);
    }

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int *client = malloc(sizeof(int));

        *client = accept(server, (struct sockaddr *)&client_addr, &client_len);
        if (client < 0) {
            perror("Failed to accept client");
            continue;
        }

        pthread_t thread;
        pthread_create(&thread, NULL, client_handler, (void *)client);
        pthread_detach(thread);
    }
}