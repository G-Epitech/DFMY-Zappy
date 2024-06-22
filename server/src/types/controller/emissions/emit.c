/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** emit.c
*/

#include <unistd.h>
#include <memory.h>
#include <errno.h>
#include "types/controller.h"
#include "log.h"
#include "types/server.h"

static bool controller_write_buffer(controller_t *controller)
{
    ssize_t written;
    size_t pending_bytes;

    pending_bytes = controller->generic.emissions->bytes;
    written = buffer_flush(controller->generic.emissions,
        controller->generic.socket
    );
    if (written == -1) {
        log_error("Failed to write to %d: %s", controller->generic.socket,
            strerror(errno));
        return false;
    }
    log_debug("%ldB/%ldB sent to %d", written, pending_bytes,
        controller->generic.socket);
    return true;
}

bool controller_emit(controller_t *controller)
{
    if (!controller)
        return false;
    if (CTRL_CAN_EMIT(controller) &&
        controller->generic.emissions->bytes > 0 &&
        controller_can_receive(controller)
    ) {
        return controller_write_buffer(controller);
    }
    return false;
}

bool controller_try_emit(controller_t *controller)
{
    server_t *server = NULL;
    bool writable = false;

    if (!controller || !CTRL_CAN_EMIT(controller))
        return false;
    server = controller->generic.server;
    if (!server)
        return false;
    writable = FD_ISSET(controller->generic.socket,
        &server->fd_actual.writable
    );
    if (writable || server_poll_controller(server, controller))
        return controller_emit(controller);
    return false;
}
