#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

typedef struct http_request http_request;
typedef struct http_response http_response;

void handle_request(char* request, int length, char* response,
                    size_t* response_length);

#endif