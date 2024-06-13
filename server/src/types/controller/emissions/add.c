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

bool controller_add_emission(controller_t *controller, smart_ptr_t *buffer_ptr,
    size_t buffer_size)
{
    emission_t *emission = emission_new(buffer_ptr, buffer_size);
    char *buffer = NULL;
    bool success = true;

    if (!emission || !buffer_ptr || !buffer_ptr->ptr)
        return false;
    buffer = SMART_PTR_CAST(char *, buffer_ptr);
    success = list_push(controller->generic.emissions,
        NODE_DATA_FROM_PTR(emission));
    if (!success) {
        log_error("Failed to add emission [%s] to controller %d", buffer,
            controller->generic.socket);
    } else {
        log_info("Added emission [%s] to controller %d", buffer,
            controller->generic.socket);
    }
    return success;
}
