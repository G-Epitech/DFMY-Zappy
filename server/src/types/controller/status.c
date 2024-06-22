/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** check.c
*/

#include "types/server.h"
#include "types/controller.h"

bool controller_has_content_to_read(controller_t *controller)
{
    server_t *server = NULL;

    if (!controller)
        return false;
    server = controller->generic.server;
    if (!server)
        return false;
    return (FD_ISSET(
        controller->generic.socket,
        &server->fd_actual.readable
    ));
}

bool controller_can_receive(controller_t *controller)
{
    server_t *server = NULL;

    if (!controller)
        return false;
    server = controller->generic.server;
    if (!server)
        return false;
    return (FD_ISSET(
        controller->generic.socket,
        &server->fd_actual.writable
    ));
}
