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

bool controller_add_emission_from_shared_buffer(controller_t *controller,
    smart_ptr_t *buffer_ptr, size_t buffer_size, int flags)
{
    emission_t *emission = emission_new(buffer_ptr, buffer_size, flags);
    char *buffer = NULL;
    bool success = false;

    if (!emission) {
        smart_ptr_free(buffer_ptr);
        return false;
    }
    buffer = SMART_PTR_CAST(char *, buffer_ptr);
    success = list_push(controller->generic.emissions,
                        NODE_DATA_FROM_PTR(emission));
    if (success) {
        log_debug("Added emission [%s] to controller %d", buffer,
            controller->generic.socket);
    } else {
        log_error("Failed to add emission [%s] to controller %d", buffer,
            controller->generic.socket);
        emission_free(emission);
    }
    return success;
}

bool controller_add_emission(controller_t *controller, char *buffer,
    size_t buffer_size, int flags)
{
    smart_ptr_t *buffer_ptr = NULL;

    if (!controller || !buffer || !CTRL_CAN_EMIT(controller))
        return false;
    buffer_ptr = smart_ptr_new(buffer);
    if (!buffer_ptr)
        return false;
    return controller_add_emission_from_shared_buffer(controller, buffer_ptr,
        buffer_size, flags);
}

bool controller_add_emission_from_format(controller_t *controller,
    int flags, char *format, ...)
{
    va_list args;
    char *buffer = NULL;
    int buffer_size = 0;
    bool success = false;

    if (!controller || !format || !CTRL_CAN_EMIT(controller))
        return false;
    va_start(args, format);
    buffer_size = my_vasprintf(&buffer, format, args);
    va_end(args);
    if (buffer_size == -1)
        return false;
    success = controller_add_emission(controller, buffer, buffer_size, flags);
    return success;
}

bool controllers_add_emission(list_t *controllers,
    emission_params_t *params, controller_type_t types)
{
    smart_ptr_t *buffer_ptr = NULL;
    controller_t *controller = NULL;
    node_t *node = controllers ? controllers->first : NULL;

    if (!controllers || !params || !params->buffer)
        return false;
    buffer_ptr = smart_ptr_new(params->buffer);
    if (!buffer_ptr)
        return false;
    while (node) {
        controller = NODE_DATA_TO_PTR(node->data, controller_t *);
        if (controller->generic.type & types && CTRL_CAN_EMIT(controller)) {
            controller_add_emission_from_shared_buffer(controller, buffer_ptr,
                params->buffer_size, params->flags);
        }
        node = node->next;
    }
    return true;
}
