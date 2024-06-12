/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** start.c
*/

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "log.h"
#include "types/server.h"

bool server_setup_socket(server_t *server)
{
    int opt = 1;

    if (!server)
        return false;
    server->socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server->socket < 0) {
        log_error("Server socket initialization failed: %s", strerror(errno));
        return false;
    }
    if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR,
        &opt, sizeof(opt)) < 0) {
        log_error("Server socket initialization failed: %s", strerror(errno));
        return false;
    }
    FD_SET(server->socket, &(server->fd_watch.readable));
    server->fd_watch.max = server->socket;
    return true;
}

bool server_setup_address(server_t *server, uint16_t port)
{
    sockaddr_in_t *address = server ? &server->address : NULL;

    if (!server)
        return false;
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(port);
    if (bind(server->socket, AS_SOCKADDR(address), sizeof(*address)) < 0) {
        log_error("Server address binding failed: %s", strerror(errno));
        return false;
    }
    return true;
}

bool server_setup_listener(server_t *server)
{
    if (!server || listen(server->socket, SOMAXCONN) < 0) {
        log_error("Unable to listen for connections: %s", strerror(errno));
        return false;
    }
    return true;
}

bool server_start(server_t *server, uint16_t port)
{
    if (!server_setup_socket(server) ||
        !server_setup_address(server, port) ||
        !server_setup_listener(server)
    ) {
        close(server->socket);
        return false;
    }
    server->running = true;
    return true;
}
