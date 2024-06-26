/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** read.c
*/

#include <unistd.h>
#include <memory.h>
#include "types/controller.h"
#include "log.h"

controller_state_t controller_read(controller_t *controller)
{
    generic_controller_t *generic = controller ? &controller->generic : NULL;
    ssize_t read_size;

    if (!controller)
        return CTRL_DISCONNECTED;
    if (buffer_is_full(controller->generic.incoming))
        return controller->generic.state;
    read_size = buffer_read_from(generic->incoming, generic->socket);
    if (read_size == 0)
        return CTRL_DISCONNECTED;
    if (read_size < 0) {
        log_error("Failed to read from socket %d", generic->socket);
    } else if (CTRL_CAN_REQ(controller)) {
        log_debug("Received %ldB from %d", read_size, generic->socket);
    }
    return generic->state;
}
