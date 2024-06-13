/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** server.h
*/

#pragma once

#include <netinet/in.h>
#include "list.h"
#include "controller.h"

// @brief Cast a pointer to a sockaddr structure
#define AS_SOCKADDR(x) ((struct sockaddr*) x)

// @brief Set of file descriptors
typedef fd_set fd_set_t;

// @brief Internet address
typedef struct sockaddr_in sockaddr_in_t;

// @brief File descriptor state write
#define FD_STATES_W 1
// @brief File descriptor state read
#define FD_STATES_R 2
// @brief File descriptor state exception
#define FD_STATES_E 4

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
 * @brief Setup server socket
 * @param server Server structure to initialize
 * @return true If setup was successful
 * @return false  If an error occurred
 */
bool server_setup_socket(server_t *server);

/**
 * @brief Setup server address
 * @param server Server structure to initialize
 * @param port Port to bind to
 * @return true If setup was successful
 * @return false  If an error occurred
 */
bool server_setup_address(server_t *server, uint16_t port);

/**
 * @brief Setup server listener
 * @param server Server structure of which setup listener
 * @return true If setup was successful
 * @return false If an error occurred
 */
bool server_setup_listener(server_t *server);

/**
 * @brief Start server
 * @param server Server to start
 * @param port Port to bind to
 * @return true If server was started successfully
 * @return false If an error occurred
 */
bool server_start(server_t *server, uint16_t port);

/**
 * @brief Check if the server has pending connections
 * @param server Server to check
 * @return Status of pending connections
 */
bool server_has_pending_connections(server_t *server);

/**
 * @brief Register a new client
 * @param server Server to register client to
 * @param socket Socket of the client to register
 * @return Controller of the registered client or NULL if an error occurred
 */
controller_t *server_register_client(server_t *server, int socket);

/**
 * @brief Accept a new connection
 * @param server Server to accept connection from
 * @return true If connection was accepted successfully
 * @return false If an error occurred
 */
controller_t *server_accept_connection(server_t *server);

/**
 * @brief Initialize given file descriptors states
 * @param states File descriptors states to initialize
 */
void fd_states_init(fd_states_t *states);

/**
 * @brief Set given file descriptor state
 * @param states File descriptors states to set
 * @param fd File descriptor to set
 * @param flags State to set
 */
void fd_states_set(fd_states_t *states, int fd, int flags);

/**
 * @brief Unset given file descriptor state
 * @param states File descriptors states to unset
 * @param fd File descriptor to unset
 * @param flags State to unset
 */
void fd_states_unset(fd_states_t *states, int fd, int flags);

/**
 * @brief Clear given file descriptor states
 * @param states File descriptors states to clear
 * @param flags States to clear
 */
void fd_states_clear(fd_states_t *states, int flags);
