/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** handle_write.c
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "log.h"
#include "types/controller.h"

ssize_t controller_write(controller_t *controller, const char *msg, size_t len)
{
    ssize_t written;

    if (!controller || !msg)
        return -1;
    written = write(controller->generic.socket, msg, len);
    if (written == -1) {
        log_error("Failed to write to %d: %s", controller->generic.socket,
            strerror(errno));
    } else {
        log_debug("%ldB/%ldB sent to %d", written, len,
            controller->generic.socket);
    }
    return written;
}

bool controller_end_emission(controller_t *controller)
{
    ssize_t written;

    if (!controller)
        return false;
    written = write(controller->generic.socket, "\n", 1);
    if (written == -1) {
        log_error("Failed to write to %d: %s", controller->generic.socket,
            strerror(errno));
        return false;
    }
    return true;
}
