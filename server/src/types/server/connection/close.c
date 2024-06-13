/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** accept.c
*/

#include <unistd.h>
#include "types/server.h"
#include "types/controller.h"

static void server_remove_controller(server_t *server, controller_t *controller)
{
    node_t *node = server->controllers->first;
    node_t *next = NULL;

    while (node) {
        next = node->next;
        if (NODE_TO_PTR(node, controller_t *) == controller) {
            list_erase(server->controllers, node, &controller_free_as_node_data);
        }
        node = next;
    }
}

void server_close_connection(server_t *server, controller_t *controller)
{
    if (!server || !controller)
        return;
    fd_states_unset(&server->fd_watch, controller->generic.socket,
        FD_STATES_R | FD_STATES_E | FD_STATES_W);
    close(controller->generic.socket);
    server_remove_controller(server, controller);
}
