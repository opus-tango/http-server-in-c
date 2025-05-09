#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

/**
 * Header file for client_handler.c
 *
 * Nothing special here
 */

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

/**
 * Handles a single client connection. Meant to be run in a separate thread.
 *
 * @param args A pointer to the file descriptor of the client
 *
 * @return NULL
 *
 * @details
 * This function is designed to be run in a separate thread. It will receive
 * requests from the client until the client disconnects, at which point it will
 * return. Reading the requests and building responses is handled by
 * handle_request.
 */
void* client_handler(void* args);

#endif