/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** handle.cpp
*/

#include "types/server.h"

void server_handle_controller_emissions(server_t *server,
    controller_t *controller)
{
    if (controller &&
        FD_ISSET(controller->generic.socket, &server->fd_actual.writable) &&
        controller->generic.emissions->len > 0
    ) {
        controller_emit(controller);
    }
}

void server_handle_emissions(server_t *server)
{
    node_t *node = server->controllers->first;
    controller_t *controller = NULL;

    while (node) {
        controller = NODE_TO_PTR(node, controller_t *);
        server_handle_controller_emissions(server, controller);
        node = node->next;
    }
}
