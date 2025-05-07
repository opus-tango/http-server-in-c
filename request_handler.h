#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "http_stuff.h"

void handle_request(char* request, int length, char* response,
                    size_t* response_length);

#endif