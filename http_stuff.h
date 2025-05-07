#ifndef HTTP_STUFF_H
#define HTTP_STUFF_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

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
    char* method;
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
http_request* free_http_request(http_request* req);

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
http_response* free_http_response(http_response* res);

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
char* reponse_to_string(http_response* res);

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

#endif