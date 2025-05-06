#include "client_handler.h"

#define BUFFER_SIZE 1024

void* client_handler(void* args) {
    int client = *((int*)args);
    char* buffer = (char*)malloc(BUFFER_SIZE);

    ssize_t bytes_read = recv(client, buffer, BUFFER_SIZE, 0);
    if (bytes_read > 0) {
        // Null terminate buffer
        buffer[bytes_read] = '\0';

        // Check if request is GET
        char* ptr = buffer;  // Modifiable pointer to buffer
        char* buf_temp =
            (char*)malloc(10);      // Temporary buffer to store request code
        char* ptr_temp = buf_temp;  // Modifiable pointer to temporary buffer
        // Copy request code to temporary buffer
        while (*ptr != ' ') {
            *ptr_temp = *ptr;
            ptr++;
            ptr_temp++;
        }
        // Null terminate temporary buffer
        *ptr_temp = '\0';
        ptr++;  // Skip over space
        if (strcmp(buf_temp, "GET") == 0) {
            printf("Received a GET request!!\n");
        } else {
            printf("Received a non-GET request!!\n");
            return NULL;
        }

        // Get filename
        char* filename = (char*)malloc(100);  // Buffer to store filename
        ptr_temp = filename;                  // Modifiable pointer to filename
        *ptr_temp = '.';                      // Prepend . to filename
        ptr_temp++;
        // Copy filename to temporary buffer
        while (*ptr != ' ') {
            // Convert %20 to space
            if (*ptr == '%' && *(ptr + 1) == '2' && *(ptr + 2) == '0') {
                ptr += 3;
                *ptr_temp = ' ';
                ptr_temp++;
            } else {
                // Copy character
                *ptr_temp = *ptr;
                ptr++;
                ptr_temp++;
            }
        }
        *ptr_temp = '\0';  // Null terminate filename

        // Print filename
        printf("Filename: %s\n", filename);

        // Send response
        char* response = "HTTP/1.1 200 OK\n\n";
        send(client, response, strlen(response), 0);

        printf("Request:\n");
        printf("%s\n", buffer);

        free(buf_temp);
        free(filename);
        return NULL;
    }
    free(buffer);
    return NULL;
}