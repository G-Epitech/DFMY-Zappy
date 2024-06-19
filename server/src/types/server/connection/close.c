/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** accept.c
*/

#include <unistd.h>
#include "types/server.h"
#include "types/controller.h"
#include "types/world/player.h"
#include "log.h"

void server_disconnect_controller(server_t *server, controller_t *controller)
{
    if (!controller) {
        log_warn("Trying to disconnect a NULL controller");
        return;
    }
    close(controller->generic.socket);
    log_info("Client on socket %d disconnected", controller->generic.socket);
    if (server) {
        fd_states_unset(&(server->fd_watch), controller->generic.socket,
            FD_STATES_R | FD_STATES_E | FD_STATES_W);
        fd_states_unset(&(server->fd_actual), controller->generic.socket,
            FD_STATES_R | FD_STATES_E | FD_STATES_W);
    }
    controller->generic.socket = -1;
    controller->generic.state = CTRL_DISCONNECTED;
}

void server_remove_disconnected_controllers(server_t *server)
{
    node_t *node = server->controllers->first;
    controller_t *controller = NULL;
    node_t *next = NULL;

    while (node) {
        next = node->next;
        controller = NODE_TO_PTR(node, controller_t *);
        if (controller->generic.state == CTRL_DISCONNECTED) {
            list_erase(server->controllers, node,
                &controller_free_as_node_data);
        }
        node = next;
    }
}

void server_close_all_connections(server_t *server)
{
    node_t *node = server->controllers->first;
    controller_t *controller = NULL;

    while (node) {
        controller = NODE_TO_PTR(node, controller_t *);
        fd_states_unset((&server->fd_watch), controller->generic.socket,
            FD_STATES_R | FD_STATES_E | FD_STATES_W);
        fd_states_unset((&server->fd_actual), controller->generic.socket,
            FD_STATES_R | FD_STATES_E | FD_STATES_W);
        close(controller->generic.socket);
        controller->generic.socket = -1;
        controller->generic.state = CTRL_DISCONNECTED;
        node = node->next;
    }
    list_clear(server->controllers, &controller_free_as_node_data);
}
