/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** server.h
*/

#pragma once

#include <netinet/in.h>
#include "list.h"
#include "shared_event.h"

// @brief Set of file descriptors
typedef fd_set fd_set_t;

// @brief Internet address
typedef struct sockaddr_in sockaddr_in_t;

// @brief File descriptor states
typedef struct fd_states_s {
    // @brief Readable file descriptors
    fd_set_t readable;
    // @brief Writable file descriptors
    fd_set_t writable;
    // @brief Exception file descriptors
    fd_set_t except;
    // @brief Maximum file descriptor
    int max;
} fd_states_t;

// @brief Server structure
typedef struct server_s {
    // @brief Server socket
    int socket;
    // @brief Server address
    sockaddr_in_t address;
    // @brief File descriptor to watch for
    fd_states_t fd_watch;
    // @brief Actual states of file descriptors that have
    // been watch by select
    fd_states_t fd_actual;
    // @brief List of clients controllers
    list_t *controllers;
    // @brief Running status of the server
    bool running;
    // @brief List of shared events to send to several clients
    list_t *events;
} server_t;

/**
 * @brief Initialize given server
 * @param server Server to initialize
 */
void server_init(server_t *server);

/**
 * @brief Create a new server
 * @return Created server or NULL if an error occurred
 */
server_t *server_new(void);

/**
 * @brief Free given server
 * @param server Server to free
 */
void server_free(server_t *server);

/**
 * @brief Initialize given file descriptors states
 * @param states File descriptors states to initialize
 */
void fd_states_init(fd_states_t *states);

/**
 * @brief Register given event to server
 * @param event Event to register
 * @return Register success status
 */
bool server_event_register(server_t *server, shared_event_t *event);

/**
 * @brief Propagate given event to subscribers
 * @param actual Actual file descriptor states
 * @param event Event to propagate
 */
void server_event_propagate(fd_states_t actual, shared_event_t *event);

/**
 * @brief Propagate first event of server
 * @param server Server to propagate event
 */
void server_event_propagate_first(server_t *server);
