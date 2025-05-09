/**
 * http_stuff.c
 *
 * This file contains functions dealing with http requests and responses, and
 * the corresponding structs defined in http_stuff.h
 *
 * Included functionality is allocation and freeing of the structs, printing for
 * debug purposes, string conversion, and utility functions for dealing with
 * headers and parsing
 */

#include "http_stuff.h"

http_request* create_http_request() {
    http_request* req = (http_request*)malloc(sizeof(http_request));
    req->method_str = NULL;
    req->url = NULL;
    req->num_headers = 0;
    req->headers = NULL;
    req->content_type = NULL;
    req->content_length = 0;
    req->body = NULL;
    return req;
}

http_response* create_http_response() {
    http_response* res = (http_response*)malloc(sizeof(http_response));
    res->status_line = NULL;
    res->num_headers = 0;
    res->headers = NULL;
    res->content_type = NULL;
    res->content_length = 0;
    res->body = NULL;
    return res;
}

void free_http_request(http_request* req) {
    if (req == NULL) {
        log_message(LOG_INFO, "Attempting to free NULL request");
        return;
    }
    if (req->method_str != NULL) {
        free(req->method_str);
        req->method_str = NULL;
    }
    if (req->url != NULL) {
        free(req->url);
        req->url = NULL;
    }
    if (req->headers != NULL) {
        for (int i = 0; i < req->num_headers; i++) {
            free(req->headers[i].key);
            req->headers[i].key = NULL;
            free(req->headers[i].value);
            req->headers[i].value = NULL;
        }
        free(req->headers);
        req->headers = NULL;
    }
    if (req->content_type != NULL) {
        free(req->content_type);
        req->content_type = NULL;
    }
    if (req->body != NULL) {
        free(req->body);
        req->body = NULL;
    }
    free(req);
    req = NULL;
}

void free_http_response(http_response* res) {
    if (res == NULL) {
        log_message(LOG_INFO, "Attempting to free NULL response");
        return;
    }
    if (res->status_line != NULL) {
        free(res->status_line);
    }
    if (res->headers != NULL) {
        for (int i = 0; i < res->num_headers; i++) {
            free(res->headers[i].key);
            free(res->headers[i].value);
        }
        free(res->headers);
    }
    if (res->content_type != NULL) {
        free(res->content_type);
    }
    if (res->body != NULL) {
        free(res->body);
    }
    free(res);
    res = NULL;
}

void print_http_request(http_request* req) {
    log_message(LOG_WARN, "Deprecated function 'print_http_request' called");
    if (req == NULL) {
        log_message(LOG_INFO, "Attempting to print NULL request");
        return;
    }

    printf("Method: %s\n", (req->method_str == NULL) ? "" : req->method_str);
    printf("URL: %s\n", (req->url == NULL) ? "" : req->url);
    printf("Headers:\n");
    for (int i = 0; i < req->num_headers; i++) {
        printf("%s: %s\n",
               (req->headers[i].key == NULL) ? "" : req->headers[i].key,
               (req->headers[i].value == NULL) ? "" : req->headers[i].value);
    }
    printf("Content-Type: %s\n",
           (req->content_type == NULL) ? "" : req->content_type);
    printf("Content-Length: %zu\n", req->content_length);
    printf("Body:\n%s\n", (req->body == NULL) ? "" : req->body);
}

void print_http_response(http_response* res) {
    log_message(LOG_WARN, "Deprecated function 'print_http_response' called");
    printf("Status Line: %s\n",
           (res->status_line == NULL) ? "" : res->status_line);
    printf("Headers:\n");
    for (int i = 0; i < res->num_headers; i++) {
        printf("%s: %s\n", res->headers[i].key, res->headers[i].value);
    }
    printf("Content-Type: %s\n",
           (res->content_type == NULL) ? "" : res->content_type);
    printf("Content-Length: %zu\n", res->content_length);
    printf("Body:\n%s\n", (res->body == NULL) ? "" : res->body);
}

char* response_to_string(http_response* res) {
    log_message(LOG_DEBUG, "Converting entire response to string");
    // Define lengths
    int total_length = 0;
    int len_newline = strlen("\r\n");
    int len_crlf = strlen("\r\n\r\n");

    char* content_lenth_str = (char*)malloc(10);
    sprintf(content_lenth_str, "%zu", res->content_length);

    // Calculate total length
    total_length += strlen(res->status_line);
    total_length += len_newline;
    for (int i = 0; i < res->num_headers; i++) {
        total_length += strlen(res->headers[i].key);
        total_length += strlen(": ");
        total_length += strlen(res->headers[i].value);
        total_length += len_newline;
    }
    total_length += strlen(res->content_type);
    total_length += len_newline;
    total_length += strlen("Content-Length: ");
    total_length += strlen(content_lenth_str);
    total_length += len_crlf;
    total_length += res->content_length;
    total_length += len_crlf;
    total_length += 1;  // For null terminator

    char* response = (char*)malloc(total_length);
    strcpy(response, res->status_line);
    strcat(response, "\r\n");
    for (int i = 0; i < res->num_headers; i++) {
        strcat(response, res->headers[i].key);
        strcat(response, ": ");
        strcat(response, res->headers[i].value);
        strcat(response, "\r\n");
    }
    strcat(response, res->content_type);
    strcat(response, "\r\n");
    strcat(response, "Content-Length: ");
    strcat(response, content_lenth_str);
    strcat(response, "\r\n\r\n");
    strcat(response, res->body);
    strcat(response, "\r\n\r\n");
    return response;
}

char* response_headers_to_string(http_response* res) {
    log_message(LOG_DEBUG, "Generating response headers string");
    // Define lengths
    int total_length = 0;
    int len_newline = strlen("\r\n");
    int len_crlf = strlen("\r\n\r\n");

    char* content_lenth_str = (char*)malloc(10);
    sprintf(content_lenth_str, "%zu", res->content_length);

    // Calculate total length
    total_length += strlen(res->status_line);
    total_length += len_newline;
    for (int i = 0; i < res->num_headers; i++) {
        total_length += strlen(res->headers[i].key);
        total_length += strlen(": ");
        total_length += strlen(res->headers[i].value);
        total_length += len_newline;
    }
    total_length += strlen(res->content_type);
    total_length += len_newline;
    total_length += strlen("Content-Length: ");
    total_length += strlen(content_lenth_str);
    total_length += len_crlf;
    total_length += 1;  // For null terminator

    char* response = (char*)malloc(total_length);
    strcpy(response, res->status_line);
    strcat(response, "\r\n");
    for (int i = 0; i < res->num_headers; i++) {
        strcat(response, res->headers[i].key);
        strcat(response, ": ");
        strcat(response, res->headers[i].value);
        strcat(response, "\r\n");
    }
    strcat(response, res->content_type);
    strcat(response, "\r\n");
    strcat(response, "Content-Length: ");
    strcat(response, content_lenth_str);
    strcat(response, "\r\n\r\n");
    free(content_lenth_str);
    return response;
}

char* get_header_value_request(http_request* req, char* key) {
    log_message(LOG_DEBUG, "Getting header value for %s", key);
    for (int i = 0; i < req->num_headers; i++) {
        if (strcmp(req->headers[i].key, key) == 0) {
            return req->headers[i].value;
        }
    }
    log_message(LOG_WARN, "Header %s not found", key);
    return NULL;
}

void request_add_header_n(http_request* req, char* key, size_t key_length,
                          char* value, size_t value_length) {
    req->num_headers++;
    req->headers = realloc(req->headers, req->num_headers * sizeof(header_kv));
    req->headers[req->num_headers - 1].key = malloc(key_length + 1);
    req->headers[req->num_headers - 1].value = malloc(value_length + 1);
    memcpy(req->headers[req->num_headers - 1].key, key, key_length);
    memcpy(req->headers[req->num_headers - 1].value, value, value_length);
    req->headers[req->num_headers - 1].key[key_length] = '\0';
    req->headers[req->num_headers - 1].value[value_length] = '\0';
    log_message(LOG_DEBUG, "Adding header %s: %s",
                req->headers[req->num_headers - 1].key,
                req->headers[req->num_headers - 1].value);
}

void request_add_header(http_request* req, char* key, char* value) {
    request_add_header_n(req, key, strlen(key), value, strlen(value));
}

void autofill_content_meta(http_request* req) {
    log_message(LOG_DEBUG, "Autofilling content metadata");
    char* cptr = get_header_value_request(req, "Content-Type");
    if (cptr != NULL) {
        req->content_type = malloc(strlen(cptr) + 1);
        strcpy(req->content_type, cptr);
    }
    cptr = get_header_value_request(req, "Content-Length");
    if (cptr != NULL) {
        req->content_length = atoi(cptr);
    }
}