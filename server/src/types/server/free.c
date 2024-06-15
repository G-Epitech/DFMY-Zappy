/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include <unistd.h>
#include "types/server.h"
#include "types/controller.h"

void server_free(server_t *server)
{
    if (!server)
        return;
    close(server->socket);
    list_free(server->controllers, &controller_free_as_node_data);
    free(server);
}
