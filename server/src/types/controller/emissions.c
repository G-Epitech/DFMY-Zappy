/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** emissions.c
*/

#include <unistd.h>
#include "types/controller.h"
#include "types/emission.h"
#include "types/list.h"

bool controller_add_emission(controller_t *controller, char *buffer,
    size_t buffer_size)
{
    emission_t *emission = emission_new(buffer, buffer_size);

    if (!emission)
        return false;
    return list_push(controller->generic.emissions,
    NODE_DATA_FROM_PTR(emission));
}

void controller_emit(controller_t *controller)
{
    emission_t *emission = NULL;
    node_t *node = NULL;
    size_t written = 0;

    if (!controller || controller->generic.emissions->len == 0)
        return;
    node = controller->generic.emissions->first;
    emission = NODE_DATA_TO_PTR(node->data, emission_t *);
    written = write(controller->generic.socket, emission->buffer,
        emission->buffer_size);
    if (written == -1)
        return;
    if (written == emission->buffer_size) {
        list_erase(controller->generic.emissions, node,
    &emission_free_as_node_data);
    } else {
        emission->buffer += written;
        emission->buffer_size -= written;
    }
}
