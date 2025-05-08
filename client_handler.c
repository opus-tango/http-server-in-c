#include "client_handler.h"

#include "request_handler.h"

#define BUFFER_SIZE 1024

/**
 * Handles a single client connection.
 *
 * @param args A pointer to the file descriptor of the client
 *
 * @return NULL
 *
 * @details
 * This function is designed to be run in a separate thread. It will receive
 * requests from the client until the client disconnects, at which point it will
 * return. Reading the requests and building responses is handled by
 * handle_request.
 */
void* client_handler(void* args) {
    // Cast args
    int client = *((int*)args);
    char* buffer = (char*)malloc(BUFFER_SIZE);

    ssize_t bytes_read = recv(client, buffer, BUFFER_SIZE, 0);
    if (bytes_read > 0) {
        // Null terminate buffer
        buffer[bytes_read] = '\0';

        // Allocate space for response
        char* response = NULL;
        size_t response_length = BUFFER_SIZE;

        // Handle request
        handle_request(buffer, bytes_read, &response, &response_length);

        // Send response
        send(client, response, response_length, 0);

        free(response);
        return NULL;
    }
    free(buffer);
    return NULL;
}