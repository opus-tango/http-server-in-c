/*
 * webserver.c
 *
 * This file contains the main function for managing sockets, clients, user
 * input, and threads.
 */

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
#include "logging.h"

struct sockaddr_in server_addr;
#define DEBUG 1

int main() {
    open_log_file();
    set_log_level(DEBUG ? LOG_DEBUG : LOG_INFO);
    // Create socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        log_message(LOG_ERROR, "Socket creation failed");
        exit(1);
    }
    log_message(LOG_INFO, "Socket created");

    // Socket address config
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    // Allow reuse of port when debugging
    if (DEBUG) {
        log_message(LOG_DEBUG, "Allowing reuse of port");
        int reuse = 1;
        setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    }

    // Bind socket
    if (bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
        0) {
        log_message(LOG_ERROR, "Socket bind failed");
        exit(1);
    }

    // Listen for connections
    if (listen(server, 5) < 0) {
        log_message(LOG_ERROR, "Socket listen failed");
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
                    shutdown(server, SHUT_RDWR);
                    log_message(LOG_INFO, "Shutting down server");
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
                if (*client < 0) {
                    log_message(LOG_ERROR, "Socket accept failed");
                    continue;
                }

                pthread_attr_t attr;
                pthread_attr_init(&attr);
                pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

                pthread_t thread;
                pthread_create(&thread, &attr, client_handler, (void *)client);
                pthread_detach(thread);

                pthread_attr_destroy(&attr);
            }
        }
    }
    close_log_file();
    return 0;
}