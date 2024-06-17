/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** handle.cpp
*/

#include "types/server.h"

controller_state_t server_handle_controller_requests(server_t *server,
    controller_t *controller)
{
    if (!controller)
        return CTRL_DISCONNECTED;
    if (server_controller_has_content_to_read(server, controller))
        return controller_read(controller);
    return CTRL_CONNECTED;
}

void server_handle_requests(server_t *server)
{
    node_t *node = NULL;
    controller_t *controller = NULL;
    controller_state_t state;

    node = server->controllers->first;
    while (node) {
        controller = NODE_TO_PTR(node, controller_t *);
        state = server_handle_controller_requests(server, controller);
        if (state == CTRL_DISCONNECTED)
            server_close_connection(server, controller);
        node = node->next;
    }
}
