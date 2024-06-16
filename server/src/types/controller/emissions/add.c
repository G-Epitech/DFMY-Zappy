/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** add.c
*/

#include <memory.h>
#include "types/controller.h"
#include "types/emission.h"
#include "types/list.h"
#include "log.h"

static bool controller_add_emission_final(controller_t *controller,
    smart_ptr_t *buffer_ptr, size_t buffer_size)
{
    emission_t *emission = NULL;
    char *buffer = NULL;
    bool success = false;

    emission = emission_new(buffer_ptr, buffer_size);
    if (!emission)
        return false;
    buffer = SMART_PTR_CAST(char *, buffer_ptr);
    success = list_push(controller->generic.emissions,
                        NODE_DATA_FROM_PTR(emission));
    if (success) {
        log_info("Added emission [%s] to controller %d", buffer,
            controller->generic.socket);
    } else {
        log_error("Failed to add emission [%s] to controller %d", buffer,
            controller->generic.socket);
        emission_free(emission);
    }
    return success;
}

bool controller_add_emission(controller_t *controller, char *buffer,
    size_t buffer_size)
{
    smart_ptr_t *buffer_ptr = NULL;
    bool success = false;

    if (!controller || !buffer)
        return false;
    buffer_ptr = smart_ptr_new(buffer);
    if (!buffer_ptr)
        return false;
    success = controller_add_emission_final(controller, buffer_ptr,
        buffer_size);
    if (!success) {
        smart_ptr_free(buffer_ptr);
    }
    return success;
}

bool controllers_add_emission(list_t *controllers, char *buffer,
    size_t buffer_size, controller_type_t types)
{
    smart_ptr_t *buffer_ptr = NULL;
    controller_t *controller = NULL;
    node_t *node = NULL;

    if (!buffer || !controllers)
        return false;
    buffer_ptr = smart_ptr_new(buffer);
    if (!buffer_ptr)
        return false;
    node = controllers->first;
    while (node) {
        controller = NODE_DATA_TO_PTR(node->data, controller_t *);
        if (controller->generic.type & types) {
            controller_add_emission_final(controller, buffer_ptr, buffer_size);
        }
        node = node->next;
    }
    return true;
}