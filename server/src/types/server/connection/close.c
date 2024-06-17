/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** accept.c
*/

#include <unistd.h>
#include "types/server.h"
#include "types/controller.h"
#include "log.h"

static void server_remove_controller(server_t *server,
    controller_t *controller)
{
    node_t *node = server->controllers->first;
    node_t *next = NULL;

    while (node) {
        next = node->next;
        if (NODE_TO_PTR(node, controller_t *) == controller) {
            list_erase(server->controllers, node,
                &controller_free_as_node_data);
        }
        node = next;
    }
}

void server_close_connection(server_t *server, controller_t *controller)
{
    if (!controller) {
        log_warn("Trying to close a NULL controller");
        return;
    }
    close(controller->generic.socket);
    log_info("Client on socket %d disconnected", controller->generic.socket);
    if (server) {
        fd_states_unset(&(server->fd_watch), controller->generic.socket,
            FD_STATES_R | FD_STATES_E | FD_STATES_W);
        fd_states_unset(&(server->fd_actual), controller->generic.socket,
            FD_STATES_R | FD_STATES_E | FD_STATES_W);
        controller->generic.socket = -1;
        server_remove_controller(server, controller);
    } else {
        controller_free(controller);
    }
}

void server_close_all_connections(server_t *server)
{
    node_t *node = server->controllers->first;
    controller_t *controller = NULL;

    while (node) {
        controller = NODE_TO_PTR(node, controller_t *);
        if (!controller)
            continue;
        fd_states_unset((&server->fd_watch), controller->generic.socket,
            FD_STATES_R | FD_STATES_E | FD_STATES_W);
        fd_states_unset((&server->fd_actual), controller->generic.socket,
            FD_STATES_R | FD_STATES_E | FD_STATES_W);
        close(controller->generic.socket);
        controller->generic.socket = -1;
        node = node->next;
    }
    list_clear(server->controllers, &controller_free_as_node_data);
}
