#include "client_handler.h"

#define BUFFER_SIZE 1024

void* client_handler(void* args) {
    int client = *((int*)args);
    char* buffer = (char*)malloc(BUFFER_SIZE);

    ssize_t bytes_read = recv(client, buffer, BUFFER_SIZE, 0);
    if (bytes_read > 0) {
        char* ptr = buffer;
        char* buf_temp[10];
        char* ptr_temp = buf_temp;
        while (*ptr != ' ') {
            *ptr_temp = *ptr;
            ptr++;
            ptr_temp++;
        }
        *ptr_temp = '\0';
        if (strcmp(buf_temp, "GET") == 0) {
            printf("Received a GET request!!\n");
        } else {
            printf("Received a non-GET request!!\n");
        }
    }
    free(buffer);
    return NULL;
}