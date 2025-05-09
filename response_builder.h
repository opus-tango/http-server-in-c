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

/**
 * Handles a GET request by serving up a file from the public directory.
 *
 * @param req The request to handle
 * @param res The response to write to
 *
 * @details
 * This function will extract the path from the request URL and attempt to
 * serve up the file at that path from the public directory. The MIME type of
 * the file is determined by the extension of the file. The function will
 * return a 404 status code if the file does not exist.
 */
void response_handle_get(http_request* req, http_response* res);

/**
 * Handles a POST request.
 *
 * @param req The request to handle
 * @param res The response to write to
 *
 * @details
 * This function is currently a stub and will always return a 501 status code.
 * It will not handle POST requests.
 */
void response_handle_post(http_request* req, http_response* res);

/**
 * Handles a DELETE request.
 *
 * @param req The request to handle
 * @param res The response to write to
 *
 * @details
 * This function is currently a stub and will always return a 501 status code.
 * It will not handle DELETE requests.
 */
void response_handle_delete(http_request* req, http_response* res);

/**
 * Handles a PUT request.
 *
 * @param req The request to handle
 * @param res The response to write to
 *
 * @details
 * This function is currently a stub and will always return a 501 status code.
 * It will not handle PUT requests.
 */
void response_handle_put(http_request* req, http_response* res);

/**
 * Builds an HTTP response for a static file.
 *
 * @param file_path The path to the file to serve
 * @param content_type The content type of the file
 * @param status_code The status code of the response
 * @param res The response to populate
 *
 * @details
 * This function opens the given file and reads it into a buffer. It will then
 * set the status line, content length, content type, and body of the given
 * response to the appropriate values. If there is an error reading the file,
 * it will set the status code to 500 and the body to an appropriate error
 * message.
 */
void response_build_static_file(char* file_path, content_type content_type,
                                status_code status_code, http_response* res);

/**
 * Serves a 404 Not Found error page.
 *
 * @param res The http_response struct to populate with the 404 response.
 *
 * @details
 * This function sets the response to serve a static 404 error HTML file
 * from the public directory. It uses the response_build_static_file function
 * to construct the response with the appropriate content type and status code.
 */
void serve_404(http_response* res);

/**
 * Serves a 500 Internal Server Error error page.
 *
 * @param res The http_response struct to populate with the 500 response.
 *
 * @details
 * This function sets the response to serve a static 500 error HTML file
 * from the public directory. It uses the response_build_static_file function
 * to construct the response with the appropriate content type and status code.
 */
void serve_500(http_response* res);

/**
 * Serves a 403 Forbidden error page.
 *
 * @param res The http_response struct to populate with the 403 response.
 *
 * @details
 * This function sets the response to serve a static 403 error HTML file
 * from the public directory. It uses the response_build_static_file function
 * to construct the response with the appropriate content type and status code.
 */
void serve_403(http_response* res);

/**
 * Serves a 501 Not Implemented error page.
 *
 * @param res The http_response struct to populate with the 501 response.
 *
 * @details
 * This function sets the response to serve a static 501 error HTML file
 * from the public directory. It uses the response_build_static_file function
 * to construct the response with the appropriate content type and status code.
 */
void serve_501(http_response* res);

/**
 * Serves a 400 Bad Request error page.
 *
 * @param res The http_response struct to populate with the 400 response.
 *
 * @details
 * This function sets the response to serve a static 400 error HTML file
 * from the public directory. It uses the response_build_static_file function
 * to construct the response with the appropriate content type and status code.
 */
void serve_400(http_response* res);

#endif