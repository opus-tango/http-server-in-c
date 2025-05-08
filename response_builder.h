#ifndef RESPONSE_BUILDER_H
#define RESPONSE_BUILDER_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "http_stuff.h"

char* response_to_string(http_response* res);

void serve_static_file(http_request* req, http_response* res);

#endif