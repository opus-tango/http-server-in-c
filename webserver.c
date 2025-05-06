#include <netinet/in.h>
#include <poll.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

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

    // Set up poll to monitor stdin and server
    struct pollfd fds[2];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[1].fd = server;
    fds[1].events = POLLIN;

    // Main loop
    while (1) {
        int ret = poll(fds, 2, 0);
        if (ret > 0) {
            // Check if stdin has data
            if (fds[0].revents & POLLIN) {
                char c;
                read(STDIN_FILENO, &c, 1);
                if (c == 'q') {
                    close(server);
                    printf("Server closed\n");
                    break;
                }
            }

            // Check if server has data
            if (fds[1].revents & POLLIN) {
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int *client = malloc(sizeof(int));

                *client = accept(server, (struct sockaddr *)&client_addr,
                                 &client_len);
                if (client < 0) {
                    perror("Failed to accept client");
                    continue;
                }

                pthread_t thread;
                pthread_create(&thread, NULL, client_handler, (void *)client);
                pthread_detach(thread);
            }
        }
    }

    return 0;
}