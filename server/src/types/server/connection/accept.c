/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** accept.c
*/

#include <unistd.h>
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
    controller_t *controller = controller_new(socket);

    if (controller &&
        !list_push(server->controllers, NODE_DATA_FROM_PTR(controller))
    ) {
        controller_free(controller);
        controller = NULL;
    }
    fd_states_set(&server->fd_watch, socket, FD_STATES_R | FD_STATES_E);
    return controller;
}

controller_t *server_accept_connection(server_t *server)
{
    sockaddr_in_t address = { 0 };
    socklen_t address_len = sizeof(address);
    controller_t *controller = NULL;
    int socket = accept(server->socket, AS_SOCKADDR(&address),
        &address_len);

    if (socket < 0) {
        log_error("Failed to accept new connection");
        return false;
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
