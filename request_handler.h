#ifndef HTTP_RESPONSE_BUILDER_H
#define HTTP_RESPONSE_BUILDER_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void handle_request(char* request, int length, char* response,
                    size_t* response_length);

#endif