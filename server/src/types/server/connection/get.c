/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** get.cpp
*/

#include "types/server.h"

controller_t *server_get_controller_by_socket(server_t *server, int socket)
{
    node_t *node = server->controllers->first;
    controller_t *controller = NULL;

    while (node) {
        controller = NODE_TO_PTR(node, controller_t *);
        if (controller->generic.socket == socket)
            return controller;
        node = node->next;
    }
    return NULL;
}
