/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** start.c
*/

#include <errno.h>
#include <string.h>
#include "log.h"
#include "types/server.h"

void server_update_fd_watch_write(server_t *server)
{
    node_t *node = server->controllers->first;
    controller_t *controller = NULL;

    fd_states_clear(&server->fd_watch, FD_STATES_W);
    while (node) {
        controller = NODE_TO_PTR(node, controller_t *);
        if (controller->generic.emissions->bytes > 0
            && CTRL_CAN_EMIT(controller)
        ) {
            fd_states_set(&server->fd_watch, controller->generic.socket,
                FD_STATES_W
            );
        }
        node = node->next;
    }
}

int server_poll(server_t *server, timeval_t *timeout)
{
    fd_states_t *actual = &server->fd_actual;
    int res = 0;

    server_update_fd_watch_write(server);
    *actual = server->fd_watch;
    res = select(actual->max + 1, &actual->readable, &actual->writable,
        &actual->except, timeout);
    if (res == -1) {
        if (errno != EINTR)
            log_error("Server polling fail: %s", strerror(errno));
        fd_states_clear(actual, FD_STATES_E | FD_STATES_W | FD_STATES_R);
        return -1;
    }
    return res;
}
