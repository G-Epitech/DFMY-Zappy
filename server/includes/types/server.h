/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** server.h
*/

#pragma once

#include "list.h"

// @brief Set of file descriptors
typedef fd_set fd_set_t;

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
