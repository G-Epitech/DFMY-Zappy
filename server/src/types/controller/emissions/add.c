/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** add.c
*/

#include <memory.h>
#include "types/controller.h"
#include "types/list.h"
#include "log.h"

static bool controller_add_emission_final(controller_t *controller,
    char *format, va_list args)
{
    ssize_t written;

    written = buffer_vwritef(controller->generic.emissions, format, args);
    if (written < 0) {
        log_error("Failed to format emission for controller %d",
            controller->generic.socket
        );
        return false;
    }
    log_debug("Added %ld bytes to emit to controller %d", written,
        controller->generic.socket);
    return true;
}

bool controller_add_emission(controller_t *controller, char *format, ...)
{
    va_list args;
    bool success = false;

    if (!controller || !CTRL_CAN_EMIT(controller))
        return false;
    va_start(args, format);
    success = controller_add_emission_final(controller, format, args);
    va_end(args);
    return success;
}

bool controllers_add_emission(list_t *controllers, controller_type_t types,
    char *format, ...)
{
    va_list args;
    va_list copy;
    controller_t *controller = NULL;
    node_t *node = controllers ? controllers->first : NULL;

    if (!controllers)
        return false;
    va_start(args, format);
    while (node) {
        va_copy(copy, args);
        controller = NODE_TO_PTR(node, controller_t *);
        if (controller->generic.type & types)
            controller_add_emission_final(controller, format, copy);
        node = node->next;
        va_end(copy);
    }
    va_end(args);
    return true;
}
