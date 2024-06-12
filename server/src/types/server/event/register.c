/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** register.c
*/

#include "log.h"
#include "types/server.h"
#include "types/controller.h"

bool server_event_register(server_t *server, shared_event_t *event)
{
    bool success = true;

    if (!event || !server)
        return false;
    success = list_push(server->events, NODE_DATA_FROM_PTR(event));
    if (!success) {
        log_error("Failed to register event %s to server", event->buffer);
    } else {
        log_info("Registered event %s to server", event->buffer);
    }
    return success;
}
