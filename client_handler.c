#include "client_handler.h"

#define BUFFER_SIZE 1024

void* client_handler(void* args) {
    int client = *((int*)args);
    char* buffer = (char*)malloc(BUFFER_SIZE);

    ssize_t bytes_read = recv(client, buffer, BUFFER_SIZE, 0);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Received: %s\n", buffer);
    }
    free(buffer);
    return NULL;
}