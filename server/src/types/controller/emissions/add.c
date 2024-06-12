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

bool controller_add_emission(controller_t *controller, char *buffer,
    size_t buffer_size)
{
    emission_t *emission = emission_new(buffer, buffer_size);
    bool success = true;

    if (!emission)
        return false;
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
