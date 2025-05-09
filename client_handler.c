/*
 * client_handler.c
 *
 * Handles a single client connection. Meant to be run in a separate thread.
 *
 * This function is designed to be run in a separate thread. It will receive
 * requests from the client until the client disconnects, at which point it will
 * return.
 */

#include "client_handler.h"

#include "request_handler.h"

#define BUFFER_SIZE 1024

void* client_handler(void* args) {
    log_message(LOG_DEBUG, "Client handler started");
    // Cast args
    int client = *((int*)args);
    char* buffer = (char*)malloc(BUFFER_SIZE);

    ssize_t bytes_read = recv(client, buffer, BUFFER_SIZE, 0);
    if (bytes_read > 0) {
        // Null terminate buffer
        buffer[bytes_read] = '\0';

        // Allocate space for response
        http_response* response = create_http_response();

        // Handle request
        handle_request(buffer, bytes_read, response);

        // Send response
        char* headers = response_headers_to_string(response);
        send(client, headers, strlen(headers), 0);
        send(client, response->body, response->content_length, 0);
        send(client, "\r\n", 2, 0);

        free(response);
        return NULL;
    }
    free(buffer);
    return NULL;
}