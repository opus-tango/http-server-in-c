#include "request_handler.h"

void parse_http_request(char* request, int length, struct http_request* req);

void handle_request(char* request, int length, char* response,
                    size_t* response_length) {
    // Terminate request with EOF so strtok stops at end of string
    request[length] = EOF;

    printf("Request ---------\n");
    printf("%s\n---------\n", request);

    printf("parsing request ---------\n");
    // Parse request into struct
    http_request req = *create_http_request();
    parse_http_request(request, length, &req);
    print_http_request(&req);
    printf("---------\n");

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
    // Get the end of the first line
    char* request_line_end = strstr(request, "\r\n");
    if (request_line_end == NULL) {
        printf("Invalid packet (end first line)\n");
        return;
    }

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
        if (header_end >= headers_end) {
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

    // Fill in content type and length
    req->content_type = get_header_value_request(req, "Content-Type");
    req->content_length = atoi(get_header_value_request(req, "Content-Length"));

    return;
};