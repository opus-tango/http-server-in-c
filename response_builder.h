#ifndef RESPONSE_BUILDER_H
#define RESPONSE_BUILDER_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "http_stuff.h"
#include "logging.h"

typedef enum {
    HTML,
    CSS,
    JS,
    PNG,
    JPG,
} content_type;

typedef enum {
    OK,
    NOT_FOUND,
    BAD_REQUEST,
    INTERNAL_SERVER_ERROR,
    FORBIDDEN,
    NOT_IMPLEMENTED,
} status_code;

void response_handle_get(http_request* req, http_response* res);

void response_handle_post(http_request* req, http_response* res);

void response_handle_delete(http_request* req, http_response* res);

void response_handle_put(http_request* req, http_response* res);

void response_build_static_file(char* file_path, content_type content_type,
                                status_code status_code, http_response* res);

void serve_404(http_response* res);

void serve_500(http_response* res);

void serve_403(http_response* res);

void serve_501(http_response* res);

void serve_400(http_response* res);

#endif