/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** accept.c
*/

#include "types/server.h"
#include "types/controller.h"
#include "log.h"

void server_restrict_controller(server_t *server, controller_t *controller,
    controller_state_t state)
{
    int sock;

    if (!server || !controller)
        return;
    sock = controller->generic.socket;
    if ((state & CTRL_ALLOW_EMIT) != CTRL_ALLOW_EMIT) {
        fd_states_unset(&(server->fd_watch),sock,FD_STATES_W);
        fd_states_unset(&(server->fd_actual),sock,FD_STATES_W);
        controller->generic.state &= ~CTRL_ALLOW_EMIT;
    }
    if ((state & CTRL_ALLOW_REQ) != CTRL_ALLOW_REQ) {
        fd_states_unset(&(server->fd_watch),sock,FD_STATES_R);
        fd_states_unset(&(server->fd_actual),sock,FD_STATES_R);
        controller->generic.state &= ~CTRL_ALLOW_REQ;
    }
}
