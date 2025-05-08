#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "http_stuff.h"
#include "response_builder.h"

void handle_request(char* request, int length, http_response* response);

#endif