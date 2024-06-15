/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** read.c
*/

#include "types/server.h"

bool server_controller_has_content_to_read(server_t *server,
    controller_t *controller)
{
    return (FD_ISSET(
        controller->generic.socket,
        &server->fd_actual.readable
    ));
}
