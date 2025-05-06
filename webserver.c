#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
// #include <pthread.h>

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
}