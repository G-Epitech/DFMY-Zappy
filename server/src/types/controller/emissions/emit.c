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

static bool controller_handle_end_emission(controller_t *controller,
    node_t *node_emission)
{
    emission_t *emission = NODE_TO_PTR(node_emission, emission_t *);
    bool partial = emission->flags & EMISSION_PARTIAL;

    if (emission->written != emission->buffer_size)
        return false;
    if (!partial && !controller_end_emission(controller))
        return false;
    list_erase(controller->generic.emissions, node_emission,
        &emission_free_as_node_data);
    return true;
}

static void controller_handle_emit_write(controller_t *controller,
    node_t *node, emission_t *emission)
{
    char *emission_buffer = SMART_PTR_CAST(char *, emission->buffer_ptr);
    ssize_t written;

    if (controller_handle_end_emission(controller, node))
        return;
    written = controller_write(controller,
        &emission_buffer[emission->written],
        emission->buffer_size - emission->written
    );
    if (written == -1)
        return;
    emission->written += written;
    controller_handle_end_emission(controller, node);
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
