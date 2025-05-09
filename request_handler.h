#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

/**
 * request_handler.h
 *
 * This file contains functions for handling an HTTP request and constructing
 * an appropriate response.
 *
 * Included functionality is parsing the request into an http_request struct,
 * and using a switch statement to call the appropriate response handler based
 * on the request type.
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "http_stuff.h"
#include "logging.h"
#include "response_builder.h"

/**
 * Handles a given HTTP request and writes the appropriate response into the
 * given http_response struct.
 *
 * @param request The request to handle
 * @param length The length of the request
 * @param response The response to write to
 *
 * @details
 * This function will parse the given request into an http_request struct using
 * parse_http_request, handle the request using one of the response_handle_*
 * functions, and then write the response back into the given http_response
 * struct. Finally, it will free the http_request struct.
 */
void handle_request(char* request, int length, http_response* response);

/**
 * Parse a given HTTP request into a struct http_request.
 *
 * @param request The HTTP request to parse
 * @param length The length of the request
 * @param req The struct to populate with the parsed request
 *
 * @return void
 *
 * @details
 * This function will parse the given HTTP request into the req struct. This
 * includes extracting the request type, URL, headers, and body. It will also
 * autofill the content metadata based on the headers.
 */
void parse_http_request(char* request, int length, struct http_request* req);

#endif