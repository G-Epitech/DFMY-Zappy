/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** accept.c
*/

#include <unistd.h>
#include <string.h>
#include "types/server.h"
#include "log.h"
#include "types/controller.h"

bool server_has_pending_connections(server_t *server)
{
    return server
        ? (FD_ISSET(server->socket, &server->fd_actual.readable))
        : false;
}

controller_t *server_register_client(server_t *server, int socket)
{
    controller_t *controller = server ? controller_new(socket) : NULL;

    if (!server || !controller)
        return NULL;
    if (!list_push(server->controllers, NODE_DATA_FROM_PTR(controller))
    ) {
        controller_free(controller);
        return NULL;
    }
    fd_states_set(&server->fd_watch, socket, FD_STATES_R | FD_STATES_E);
    controller_add_emission(controller, strdup("WELCOME"), 7, 0);
    return controller;
}

controller_t *server_accept_connection(server_t *server)
{
    sockaddr_in_t address = { 0 };
    socklen_t address_len = sizeof(address);
    controller_t *controller = NULL;
    int socket = server ? accept(server->socket, AS_SOCKADDR(&address),
        &address_len) : -1;

    if (socket < 0) {
        log_error("Failed to accept new connection");
        return NULL;
    }
    controller = server_register_client(server, socket);
    if (!controller) {
        close(socket);
        log_error("Failed to create controller for socket %d. "
            "Socket closed.", socket);
        return NULL;
    }
    log_info("New client connected on socket %d", socket);
    return controller;
}

void server_handle_new_connections(server_t *server)
{
    if (server_has_pending_connections(server))
        server_accept_connection(server);
}
