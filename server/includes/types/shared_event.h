/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** emission.h
*/

#pragma once

#include "list.h"

// @brief Buffer writing section size for shared event
#define SHARED_EVENT_BUFF_SIZE 4096

// @brief Represent event data to emit to several clients
typedef struct shared_event_s {
    // @brief Buffer for event content
    char *buffer;
    // @brief Buffer size
    size_t buffer_size;
    // @brief Remaining clients of which send event
    list_t *subscribers;
} shared_event_t;

/**
 * @brief Create a new shared event
 * @param buffer Buffer for event content
 * @param buffer_size Buffer size
 * @return Created shared event or NULL if failed
 * @warning The ownership of buffer will be transferred to the shared event.
 */
shared_event_t *shared_event_new(char *buffer, size_t buffer_size);

/**
 * @brief Free given shared event
 * @param event Shared event to free
 */
void shared_event_free(shared_event_t *event);

/**
 * @brief Free given shared event as node data
 * @param data Shared event to free
 */
void shared_event_free_as_node_data(node_data_t data);
