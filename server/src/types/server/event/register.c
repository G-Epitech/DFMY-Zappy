/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** register.c
*/

#include "types/server.h"
#include "types/controller.h"

bool server_event_register(server_t *server, shared_event_t *event)
{
    if (!event || !server)
        return false;
    return list_push(server->events, NODE_DATA_FROM_PTR(event));
}
