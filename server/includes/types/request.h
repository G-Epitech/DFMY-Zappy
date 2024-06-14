/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** request.h
*/

#pragma once

#include "list.h"

// @brief Size of request buffer section
#define REQ_BUFF_SIZE 4096

// Max size of a request buffer
#define REQ_MAX_BUFF_SIZE (10 * REQ_BUFF_SIZE)

// @brief Request token
typedef struct request_token_s {
    // @brief Token content
    char *content;
    // @brief Token size
    size_t size;
} request_token_t;

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

/**
 * @brief Append given data to request buffer
 * @param request Request to append data to
 * @param data Data to append
 * @param size Size of data (must be less or equal to REQUEST_BUFF_SIZE)
 */
bool request_append(request_t *request, const char *data, size_t size);
