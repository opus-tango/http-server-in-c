#include "request_handler.h"

void parse_http_request(char* request, int length, struct http_request* req);
void debug_print_request(char* request);

void handle_request(char* request, int length, http_response* response) {
    // Terminate request with EOF so strtok stops at end of string
    request[length] = EOF;

    // Parse request into struct
    http_request* req = create_http_request();
    parse_http_request(request, length, req);

    // Switch statement to handle different request types
    switch (req->method) {
        case GET:
            // Build response
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

    // Create response

    // Create response string
    // char* ptr_temp = response;
    // char* temp =
    //     "HTTP/1.1 200 OK\r\nContent-Type: text/html \r\nContent-Length: "
    //     "0\r\n\r\n\0";
    // strcpy(ptr_temp, temp);

    // printf("Response --------\n");
    // printf("%s\n--------\n", response);

    // *response_length = strlen(response);

    free_http_request(req);
}

void parse_http_request(char* request, int length, struct http_request* req) {
    // Get the end of the first line
    char* request_line_end = strstr(request, "\r\n");
    if (request_line_end == NULL) {
        printf("Invalid packet (end first line)\n");
        return;
    }

    // Extract request method
    char* type_start = request;
    char* type_end = strstr(type_start, " ");
    if (type_end == NULL) {
        printf("Invalid packet (method)\n");
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
        printf("Invalid packet (method)\n");
        return;
    }
    req->method_str = (char*)malloc(type_end - type_start + 1);
    strncpy(req->method_str, type_start, type_end - type_start);
    req->method_str[type_end - type_start] = '\0';

    // Extract URL
    char* url_start = type_end + 1;
    char* url_end = strstr(url_start, " ");
    if (url_end == NULL) {
        printf("Invalid packet (url)\n");
        return;
    }
    req->url = (char*)malloc(url_end - url_start + 1);
    strncpy(req->url, url_start, url_end - url_start);
    req->url[url_end - url_start] = '\0';

    // Extract headers
    char* headers_end = strstr(request_line_end + 2, "\r\n\r\n");
    if (headers_end == NULL) {
        printf("Invalid packet (headers)\n");
        return;
    }
    char* headers_start = request_line_end + 2;
    if (headers_start == NULL) {
        printf("Invalid packet (headers)\n");
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
            printf("Invalid packet (headers)\n");
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

void debug_print_request(char* request) {
    // Copy request
    char* request_copy = (char*)malloc(strlen(request) + 1);
    strcpy(request_copy, request);

    // Iterate through request and print "\\r\\n" before each \r\n
    // and "\\r\\n\\r\\n" before each \r\n\r\n
    char* ptr = request_copy;
    while (*ptr != '\0') {
        if (*ptr == '\r' && *(ptr + 1) == '\n') {
            if (*(ptr + 2) == '\r' && *(ptr + 3) == '\n') {
                printf("\\r\\n\\r\\n\n");
                ptr += 4;
            } else {
                printf("\\r\\n\n");
                ptr += 2;
            }
        } else {
            printf("%c", *ptr);
            ptr++;
        }
    }
    printf("\n");
}