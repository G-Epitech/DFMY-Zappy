/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** handle.cpp
*/

#include "types/server.h"

void server_handle_emissions(server_t *server)
{
    node_t *node = server->controllers->first;
    controller_t *controller = NULL;

    while (node) {
        controller = NODE_TO_PTR(node, controller_t *);
        controller_emit(controller);
        node = node->next;
    }
}
