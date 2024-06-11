/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** request.h
*/

#pragma once

#include "list.h"

// @brief Size of request buffer section
#define REQUEST_BUFF_SIZE 4096

// @brief Request status
typedef enum request_status_e {
    // @brief Request is pending, not fully received
    REQ_PENDING,
    // @brief Request is ready to be handled
    REQ_READY,
    // @brief Request is fully received but unable to
    // be handled (not correctly terminated...)
    REQ_INVALID,
    // @brief Request is being handled
    REQ_HANDLING,
    // @brief The request has been processed
    REQ_FINISHED
} request_status_t;

// @brief Represent a client request
typedef struct request_s {
    // @brief Buffer for request content
    char *buffer;
    // @brief Size of buffer
    size_t buffer_size;
    // @brief Size of content in buffer
    size_t content_size;
    // @brief Status of request
    request_status_t status;
} request_t;

/**
 * @brief Initialize given request
 * @param request Request to initialize
 */
void request_init(request_t *request);

/**
 * @brief Create a new request with one buffer section
 * @return Created request or NULL if an error occurred
 */
request_t *request_new(void);

/**
 * @brief Free given request
 * @param request Request to free
 */
void request_free(request_t *request);

/**
 * @brief Free given request as node data
 * @param data Node data to free as request
 */
void request_free_as_node_data(node_data_t data);