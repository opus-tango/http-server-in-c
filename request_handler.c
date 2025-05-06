
#include "request_handler.h"

void handle_request(char* request, int length, char* response,
                    size_t* response_length) {
    request[length] = '\0';  // Null terminate request for printing

    printf("Request ---------\n");
    printf("%s\n---------\n", request);

    // Check if request is GET
    char* ptr = request;  // Modifiable pointer to request
    char buf_temp[10];    // Temporary buffer to store request code
    char* ptr_temp =
        (char*)&buf_temp;  // Modifiable pointer to temporary buffer
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
        return;
    }

    // Get filename from request url
    char filename[100];           // Buffer to store filename
    ptr_temp = (char*)&filename;  // Modifiable pointer to filename
    *ptr_temp = '.';              // Prepend . to filename
    ptr_temp++;
    // While loop to copy filename to temporary buffer
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

    // Create reponse string
    ptr_temp = response;
    char* temp = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
    while (*temp != '\0') {
        *ptr_temp = *temp;
        ptr_temp++;
        temp++;
    }
    // Put the filename in the html response
    temp = filename;
    while (*temp != '\0') {
        *ptr_temp = *temp;
        ptr_temp++;
        temp++;
    }

    *ptr_temp = '\0';  // Null terminate response

    printf("Response --------\n");
    printf("%s\n--------\n", response);

    *response_length = strlen(response);
}