#include "client_handler.h"

#include "request_handler.h"

#define BUFFER_SIZE 1024

void* client_handler(void* args) {
    int client = *((int*)args);
    char* buffer = (char*)malloc(BUFFER_SIZE);

    ssize_t bytes_read = recv(client, buffer, BUFFER_SIZE, 0);
    if (bytes_read > 0) {
        // Null terminate buffer
        buffer[bytes_read] = '\0';

        char* response = (char*)malloc(BUFFER_SIZE);
        size_t response_length = BUFFER_SIZE;

        handle_request(buffer, bytes_read, response, &response_length);

        // Send response
        send(client, response, response_length, 0);

        free(response);
        return NULL;
    }
    free(buffer);
    return NULL;
}