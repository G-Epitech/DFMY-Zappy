/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/server.h"

void server_init(server_t *server)
{
    server->socket = -1;
    server->running = false;
    fd_states_init(&server->fd_actual);
    fd_states_init(&server->fd_watch);
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
}

server_t *server_new(void)
{
    server_t *server = calloc(1, sizeof(server_t));

    if (!server)
        return NULL;
    server->controllers = list_new();
    server->events = list_new();
    if (!server->controllers || !server->events) {
        server_free(server);
        return NULL;
    }
    server_init(server);
    return server;
}
