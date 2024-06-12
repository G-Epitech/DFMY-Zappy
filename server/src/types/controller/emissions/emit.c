/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** emit.c
*/

#include <unistd.h>
#include <memory.h>
#include "log.h"
#include "types/controller.h"
#include "types/emission.h"
#include "types/list.h"

static void controller_handle_emit_write(controller_t *controller,
    node_t *node, emission_t *emission)
{
    ssize_t written;

    written = write(controller->generic.socket, emission->buffer,
                    emission->buffer_size);
    if (written == -1) {
        log_error("Failed to write to %d", controller->generic.socket);
        return;
    }
    log_debug("-> sent %ld of %ld bytes to %d", written, emission->buffer_size,
              controller->generic.socket);
    if (written == emission->buffer_size) {
        list_erase(controller->generic.emissions, node,
            &emission_free_as_node_data);
    } else {
        memmove(emission->buffer, emission->buffer + written,
            emission->buffer_size - written);
        emission->buffer_size -= written;
    }
}

void controller_emit(controller_t *controller)
{
    emission_t *emission = NULL;
    node_t *node = NULL;

    if (!controller || !controller->generic.emissions ||
        controller->generic.emissions->len == 0)
        return;
    node = controller->generic.emissions->first;
    emission = NODE_DATA_TO_PTR(node->data, emission_t *);
    controller_handle_emit_write(controller, node, emission);
}
