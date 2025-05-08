#ifndef HTTP_STUFF_H
#define HTTP_STUFF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef enum {
    GET,
    POST,
    PUT,
    DELETE,
} http_method;

/**
 * Stores a key-value pair for http headers
 */
struct header_kv {
    char* key;
    char* value;
};

/**
 * Stores an HTTP request
 */
struct http_request {
    http_method method;
    char* method_str;
    char* url;
    int num_headers;
    struct header_kv* headers;
    char* content_type;
    size_t content_length;
    char* body;
};

/**
 * Stores an HTTP response
 */
struct http_response {
    char* status_line;
    int num_headers;
    struct header_kv* headers;
    char* content_type;
    size_t content_length;
    char* body;
};

typedef struct header_kv header_kv;
typedef struct http_request http_request;
typedef struct http_response http_response;

/**
 * Creates a new http_request struct with all values set to NULL/0.
 *
 * @return A pointer to the newly allocated http_request struct.
 *
 * @details
 * The caller is responsible for freeing the returned struct when it is no
 * longer needed.
 */
http_request* create_http_request();

/**
 * Allocates memory for a new http_response struct and sets all its fields to 0
 * or NULL. This function is used to create a new empty http_response which can
 * then be populated with data.
 *
 * @return A pointer to the new http_response struct
 *
 * @details
 * The caller is responsible for freeing the returned struct when it is no
 * longer needed.
 */
http_response* create_http_response();

/**
 * Frees the memory associated with an http_request struct. This function is
 * meant to be used to free the memory associated with a request after it has
 * been processed. It returns NULL so that the return value can be used to set
 * the value of the pointer passed to it. I.e.
 *
 * http_request* req = create_http_request();
 *
 * req = free_http_request(req);
 *
 * @param req The request to free
 *
 * @return NULL
 */
void free_http_request(http_request* req);

/**
 * Frees the memory associated with an http_response struct. This function is
 * meant to be used to free the memory associated with a response after it has
 * been sent. It returns NULL so that the return value can be used to set the
 * value of the pointer passed to it. I.e.
 *
 * http_response* res = create_http_response();
 *
 * res = free_http_response(res);
 *
 * @param res The response to free
 *
 * @return NULL
 *
 * @details
 *
 */
void free_http_response(http_response* res);

/**
 * Prints a formatted version of an http_request struct to stdout. This function
 * is meant to be used for debugging purposes.
 *
 * @param req The request to print
 */
void print_http_request(http_request* req);

/**
 * Prints a formatted version of an http_response struct to stdout. This
 * function is meant to be used for debugging purposes.
 *
 * @param res The response to print
 */
void print_http_response(http_response* res);

/**
 * Converts an http_response struct to a string in the format of a HTTP
 * response. This function is meant to be used when sending a response over a
 * socket. It allocates memory for the string and returns a pointer to it, so
 * the caller is responsible for freeing the memory when it is no longer
 * needed.
 *
 * @param res The response to convert to a string
 *
 * @return A pointer to the string representation of the response
 */
char* response_to_string(http_response* res);

/**
 * Returns the string representation of an http_response struct WITHOUT the
 * body. This function is meant to be used when sending a response over a
 * socket. It allocates memory for the string and returns a pointer to it, so
 * the caller is responsible for freeing the memory when it is no longer
 * needed.
 *
 * @param res The response to convert to a string
 *
 * @return A pointer to the string representation of the response
 */
char* response_headers_to_string(http_response* res);

/**
 * Finds the value associated with a given key in an http_request's headers.
 *
 * @param req The request to search
 * @param key The key to search for
 *
 * @return The char* associated with the given key, or NULL if the key is not
 * present in the request's headers
 */
char* get_header_value_request(http_request* req, char* key);

/**
 * Adds a new header to an http_request struct with the given key and value.
 *
 * @param req The request to add the header to
 * @param key The key of the header
 * @param key_length The length of the key
 * @param value The value of the header
 * @param value_length The length of the value
 *
 * @details
 * This function is meant to be used when the lengths of the key and value are
 * already known. It is more efficient than request_add_header, which calls
 * strlen to get the lengths of the key and value.
 */
void request_add_header_n(http_request* req, char* key, size_t key_length,
                          char* value, size_t value_length);

/**
 * Adds a header to the given HTTP request.
 *
 * @param req The request to add the header to
 * @param key The key of the header to add
 * @param value The value of the header to add
 *
 * @details
 * This is a convenience function for request_add_headern. It will add a header
 * with the given key and value to the given request. It will automatically
 * calculate the length of the key and value.
 */
void request_add_header(http_request* req, char* key, char* value);

/**
 * Prints out information about an HTTP request, in a way that is not
 * particularly human-readable. This function is used for debugging
 * purposes.
 *
 * @param req The request to print information about
 */
void request_info_print(http_request* req);

/**
 * Automatically fills in the Content-Type and Content-Length fields of the
 * given http_request if they are not already set. This function is meant to be
 * used when the content type and length are not known when the request is
 * created, but are known when the request is processed.
 *
 * @param req The request whose Content-Type and Content-Length fields are to
 * be filled in
 *
 * @details
 * This function will search for the Content-Type and Content-Length headers in
 * the request. If it finds either of them, it will copy the value of the header
 * into the appropriate field in the request. If it does not find either of
 * them, it does nothing.
 */
void autofill_content_meta(http_request* req);

#endif