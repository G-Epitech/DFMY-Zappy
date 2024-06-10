/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/server.h"
#include "types/controller.h"
#include "types/shared_event.h"

void server_free(server_t *server)
{
    if (!server)
        return;
    list_free(server->controllers, &controller_free_as_node_data);
    list_free(server->events, &shared_event_free_as_node_data);
    free(server);
}
