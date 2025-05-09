/**
 * request_handler.c
 *
 * This file contains functions for handling an HTTP request and constructing
 * an appropriate response.
 *
 * Included functionality is parsing the request into an http_request struct,
 * and using a switch statement to call the appropriate response handler based
 * on the request type.
 */

#include "request_handler.h"

void handle_request(char* request, int length, http_response* response) {
    log_message(LOG_DEBUG, "Handling request");
    // Parse request into struct
    http_request* req = create_http_request();
    parse_http_request(request, length, req);

    // Switch statement to handle different request types
    switch (req->method) {
        case GET:
            response_handle_get(req, response);
            break;

        case POST:
            response_handle_post(req, response);
            break;

        case PUT:
            response_handle_put(req, response);
            break;

        case DELETE:
            response_handle_delete(req, response);
            break;
    }

    free_http_request(req);
}

void parse_http_request(char* request, int length, struct http_request* req) {
    log_message(LOG_DEBUG, "Parsing request");
    // Get the end of the first line
    char* request_line_end = strstr(request, "\r\n");
    if (request_line_end == NULL) {
        log_message(LOG_ERROR, "Invalid packet (request line), cannot parse");
        return;
    }

    // Extract request method
    char* type_start = request;
    char* type_end = strstr(type_start, " ");
    if (type_end == NULL) {
        log_message(LOG_ERROR, "Invalid packet (method), cannot parse");
        return;
    }
    char* type = (char*)malloc(type_end - type_start + 1);
    strncpy(type, type_start, type_end - type_start);
    type[type_end - type_start] = '\0';
    if (strcmp(type, "GET") == 0) {
        req->method = GET;
    } else if (strcmp(type, "POST") == 0) {
        req->method = POST;
    } else if (strcmp(type, "PUT") == 0) {
        req->method = PUT;
    } else if (strcmp(type, "DELETE") == 0) {
        req->method = DELETE;
    } else {
        log_message(LOG_ERROR, "Invalid packet (method), cannot parse");
        free(type);
        return;
    }
    req->method_str = (char*)malloc(type_end - type_start + 1);
    strncpy(req->method_str, type_start, type_end - type_start);
    req->method_str[type_end - type_start] = '\0';
    free(type);

    // Extract URL
    char* url_start = type_end + 1;
    char* url_end = strstr(url_start, " ");
    if (url_end == NULL) {
        log_message(LOG_ERROR, "Invalid packet (url), cannot parse");
        return;
    }
    req->url = (char*)malloc(url_end - url_start + 1);
    strncpy(req->url, url_start, url_end - url_start);
    req->url[url_end - url_start] = '\0';

    // Extract headers
    char* headers_end = strstr(request_line_end + 2, "\r\n\r\n");
    if (headers_end == NULL) {
        log_message(LOG_ERROR, "Invalid packet (headers), cannot parse");
        return;
    }
    char* headers_start = request_line_end + 2;
    if (headers_start == NULL) {
        log_message(LOG_ERROR, "Invalid packet (headers), cannot parse");
        return;
    }
    req->num_headers = 0;
    char* header_start = headers_start;
    while (1) {
        char* header_end = strstr(header_start, "\r\n");
        if (header_start >= headers_end) {
            break;
        }
        char* delim = strstr(header_start, ": ");
        if (delim == NULL) {
            log_message(LOG_ERROR, "Invalid packet (headers), cannot parse");
            return;
        }

        request_add_header_n(req, header_start, delim - header_start, delim + 2,
                             header_end - (delim + 2));
        header_start = header_end + 2;
    }

    // Autofill content metadata based on headers
    autofill_content_meta(req);

    // Extract body
    char* body_start = headers_end + 4;
    req->body = (char*)malloc(length - (body_start - request) + 1);
    strncpy(req->body, body_start, length - (body_start - request));
    req->body[length - (body_start - request)] = '\0';

    return;
};