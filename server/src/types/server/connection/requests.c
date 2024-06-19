/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** handle.cpp
*/

#include "types/server.h"

void server_handle_controller_requests(server_t *server,
    controller_t *controller)
{
    if (!controller || !CTRL_CAN_REQ(controller))
        return;
    if (!server_controller_has_content_to_read(server, controller))
        return;
    if (controller_read(controller) == CTRL_DISCONNECTED)
        server_disconnect_controller(server, controller);
}

void server_handle_requests(server_t *server)
{
    node_t *node = NULL;
    controller_t *controller = NULL;

    node = server->controllers->first;
    while (node) {
        controller = NODE_TO_PTR(node, controller_t *);
        server_handle_controller_requests(server, controller);
        node = node->next;
    }
}
