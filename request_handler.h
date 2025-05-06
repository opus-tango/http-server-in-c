#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

struct http_request {
    char* method;
    char* url;
    char** headers;
    int num_headers;
    char* body;
    size_t body_length;
};

struct http_response {
    char* status_line;
    char** headers;
    int num_headers;
    char* body;
    size_t body_length;
};

typedef struct http_request http_request;
typedef struct http_response http_response;

void handle_request(char* request, int length, char* response,
                    size_t* response_length);

#endif