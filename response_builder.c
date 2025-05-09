#include "response_builder.h"

void response_handle_get(http_request* req, http_response* res) {
    // Extract the path from the request URL
    char* basepath = "./public";
    char* file_path = (char*)malloc(strlen(req->url) + strlen(basepath) + 1);
    strcpy(file_path, basepath);
    strcat(file_path, req->url);
    printf("%s\n", file_path);

    // Determine the file type
    char* ptr = file_path + strlen(file_path) - 1;
    while (*ptr != '.') {
        ptr--;
    }
    if (strcmp(ptr, ".html") == 0) {
        response_build_static_file(file_path, HTML, OK, res);
    } else if (strcmp(ptr, ".jpg") == 0) {
        response_build_static_file(file_path, JPG, OK, res);
    } else if (strcmp(ptr, ".png") == 0) {
        response_build_static_file(file_path, PNG, OK, res);
    } else if (strcmp(ptr, ".css") == 0) {
        response_build_static_file(file_path, CSS, OK, res);
    } else if (strcmp(ptr, ".js") == 0) {
        response_build_static_file(file_path, JS, OK, res);
    } else {
        serve_404(res);
        return;
    }
}

void response_handle_post(http_request* req, http_response* res) {
    // TODO
    printf("POST request\n");
    printf("%s\n", req->url);
    serve_501(res);
}

void response_handle_delete(http_request* req, http_response* res) {
    // TODO
    printf("DELETE request\n");
    printf("%s\n", req->url);
    serve_501(res);
}

void response_handle_put(http_request* req, http_response* res) {
    // TODO
    printf("PUT request\n");
    printf("%s\n", req->url);
    serve_501(res);
}

void response_build_static_file(char* file_path, content_type content_type,
                                status_code status_code, http_response* res) {
    // Open the file and verify that the file exists
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("fopen failed to find file %s\n", file_path);
        serve_404(res);
        return;
    }

    // Get filesize
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read file into buffer
    char* file_buffer = (char*)malloc(file_size);
    if (file_buffer == NULL) {
        printf("malloc failed\n");
        serve_500(res);
        return;
    }
    size_t bytes_read = fread(file_buffer, file_size, 1, file);
    if (bytes_read != 1) {
        printf("fread failed\n");
        serve_500(res);
        return;
    }
    fclose(file);

    // Set content length
    res->content_length = file_size;

    // Set body
    res->body = file_buffer;

    // Create status line
    char* status_line = (char*)malloc(48);
    strcpy(status_line, "HTTP/1.1 ");
    switch (status_code) {
        case OK:
            strcat(status_line, "200 OK");
            break;

        case NOT_FOUND:
            strcat(status_line, "404 Not Found");
            break;

        case BAD_REQUEST:
            strcat(status_line, "400 Bad Request");
            break;

        case INTERNAL_SERVER_ERROR:
            strcat(status_line, "500 Internal Server Error");
            break;

        case FORBIDDEN:
            strcat(status_line, "403 Forbidden");
            break;

        default:
            strcat(status_line, "501 Not Implemented");
            break;
    }
    // Set status line
    res->status_line = status_line;

    // Create content type string
    char* content_type_str;

    switch (content_type) {
        case HTML:
            content_type_str =
                (char*)malloc(strlen("Content-Type: text/html") + 1);
            strcpy(content_type_str, "Content-Type: text/html");
            break;

        case CSS:
            content_type_str =
                (char*)malloc(strlen("Content-Type: text/css") + 1);
            strcpy(content_type_str, "Content-Type: text/css");
            break;

        case JS:
            content_type_str =
                (char*)malloc(strlen("Content-Type: text/javascript") + 1);
            strcpy(content_type_str, "text/javascript");
            break;

        case PNG:
            content_type_str =
                (char*)malloc(strlen("Content-Type: image/png") + 1);
            strcpy(content_type_str, "Content-Type: image/png");
            break;

        case JPG:
            content_type_str =
                (char*)malloc(strlen("Content-Type: image/jpeg") + 1);
            strcpy(content_type_str, "Content-Type: image/jpeg");
            break;
    }
    // Set content type string
    res->content_type = content_type_str;

    // Add header for close connection
    header_kv* close_connection = (header_kv*)malloc(sizeof(header_kv));
    close_connection->key = (char*)malloc(strlen("Connection") + 1);
    close_connection->value = (char*)malloc(strlen("close") + 1);
    strcpy(close_connection->key, "Connection");
    strcpy(close_connection->value, "close");
    res->headers = close_connection;
    res->num_headers = 1;
}

void serve_404(http_response* res) {
    char* file_path = "./public/404.html";
    response_build_static_file(file_path, HTML, NOT_FOUND, res);
}

void serve_500(http_response* res) {
    char* file_path = "./public/500.html";
    response_build_static_file(file_path, HTML, INTERNAL_SERVER_ERROR, res);
}

void serve_403(http_response* res) {
    char* file_path = "./public/403.html";
    response_build_static_file(file_path, HTML, FORBIDDEN, res);
}

void serve_501(http_response* res) {
    char* file_path = "./public/501.html";
    response_build_static_file(file_path, HTML, NOT_IMPLEMENTED, res);
}

void serve_400(http_response* res) {
    char* file_path = "./public/400.html";
    response_build_static_file(file_path, HTML, BAD_REQUEST, res);
}