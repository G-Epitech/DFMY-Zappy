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

void controller_emit(controller_t *controller)
{
    ssize_t written;
    size_t pending_bytes;

    if (!controller)
        return;
    pending_bytes = controller->generic.emissions->bytes;
    written = buffer_flush(controller->generic.emissions,
        controller->generic.socket
    );
    if (written == -1) {
        log_error("Failed to write to %d: %s", controller->generic.socket,
            strerror(errno));
    } else {
        log_debug("%ldB/%ldB sent to %d", written, pending_bytes,
            controller->generic.socket);
    }
}
