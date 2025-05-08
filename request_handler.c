#include "request_handler.h"

void parse_http_request(char* request, int length, struct http_request* req);
void debug_print_request(char* request);

void handle_request(char* request, int length, char* response,
                    size_t* response_length) {
    // Terminate request with EOF so strtok stops at end of string
    request[length] = EOF;

    // printf("Request ---------\n");
    // printf("%s\n---------\n", request);

    debug_print_request(request);

    printf("parsing request ---------\n");
    // Parse request into struct
    http_request* req = create_http_request();
    parse_http_request(request, length, req);
    print_http_request(req);
    // request_info_print(req);

    printf("---------\n");
    free_http_request(req);
    printf("req pointer value: %d\n", (int)req);

    // Create reponse string
    char* ptr_temp = response;
    char* temp =
        "HTTP/1.1 200 OK\r\nContent-Type: text/html \r\nContent-Length: "
        "0\r\n\r\n\0";
    strcpy(ptr_temp, temp);
    // while (*temp != '\0') {
    //     *ptr_temp = *temp;
    //     ptr_temp++;
    //     temp++;
    // }
    // // Put content length in the html response
    // int content_length = strlen(filename);
    // char content_length_str[10];
    // sprintf(content_length_str, "%d", content_length);
    // temp = (char*)&content_length_str;
    // while (*temp != '\0') {
    //     *ptr_temp = *temp;
    //     ptr_temp++;
    //     temp++;
    // }
    // // Terminate header
    // temp = "\r\n\r\n\0";
    // while (*temp != '\0') {
    //     *ptr_temp = *temp;
    //     ptr_temp++;
    //     temp++;
    // }
    // // Put the filename in the html response
    // temp = filename;
    // while (*temp != '\0') {
    //     *ptr_temp = *temp;
    //     ptr_temp++;
    //     temp++;
    // }

    // *ptr_temp = '\0';  // Null terminate response

    printf("Response --------\n");
    printf("%s\n--------\n", response);

    *response_length = strlen(response);
}

void parse_http_request(char* request, int length, struct http_request* req) {
    // printf("Parsing request\n");
    // Get the end of the first line
    char* request_line_end = strstr(request, "\r\n");
    if (request_line_end == NULL) {
        printf("Invalid packet (end first line)\n");
        return;
    }
    // printf("Parsed request line end\n");

    // Extract request type
    char* type_start = request;
    char* type_end = strstr(type_start, " ");
    if (type_end == NULL) {
        printf("Invalid packet (method)\n");
        return;
    }
    req->method = (char*)malloc(type_end - type_start + 1);
    strncpy(req->method, type_start, type_end - type_start);
    req->method[type_end - type_start] = '\0';
    // printf("Parsed request type\n");

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
    // printf("Parsed request url\n");

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
    // printf("Parsed request headers\n");

    // Fill in content type and length. In order to avoid a double free we copy
    // the content type instead of just pointing to the request header
    req->content_type =
        malloc(strlen(get_header_value_request(req, "Content-Type")) + 1);
    strcpy(req->content_type, get_header_value_request(req, "Content-Type"));
    req->content_length = atoi(get_header_value_request(req, "Content-Length"));
    // printf("Parsed request content type and length\n");

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