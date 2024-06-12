/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** handle_write.c
*/

#include <unistd.h>
#include "log.h"
#include "types/controller.h"

ssize_t controller_write(controller_t *controller, const char *msg, size_t len)
{
    ssize_t written;

    if (!controller || !msg)
        return -1;
    written = write(controller->generic.socket, msg, len);
    if (written == -1) {
        log_error("Failed to write to %d", controller->generic.socket);
    } else {
        log_debug("-> sent %ld of %ld bytes to %d", written, len,
                  controller->generic.socket);
    }
    return written;
}
