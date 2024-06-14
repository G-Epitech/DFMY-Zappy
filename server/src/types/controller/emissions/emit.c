/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** emit.c
*/

#include <unistd.h>
#include <memory.h>
#include "types/controller.h"
#include "types/emission.h"
#include "types/list.h"

static void controller_handle_emit_write(controller_t *controller,
    node_t *node, emission_t *emission)
{
    char *emission_buffer = SMART_PTR_CAST(char *, emission->buffer_ptr);
    ssize_t written = controller_write(controller,
        &emission_buffer[emission->written],
        emission->buffer_size - emission->written);

    if (written == emission->buffer_size) {
        list_erase(controller->generic.emissions, node,
            &emission_free_as_node_data);
    } else {
        emission->written += written;
    }
}

void controller_emit(controller_t *controller)
{
    emission_t *emission = NULL;
    node_t *node = NULL;

    if (!controller)
        return;
    node = controller->generic.emissions->first;
    while (node) {
        emission = NODE_DATA_TO_PTR(node->data, emission_t *);
        controller_handle_emit_write(controller, node, emission);
        node = node->next;
    }
}
