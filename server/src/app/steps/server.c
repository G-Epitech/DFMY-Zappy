/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** server.c
*/

#include "app.h"

void app_handle_server_logic(app_t *app)
{
    timeval_t timeout = { 10, 0 };

    if (server_poll(app->server, &timeout) > 0) {
        server_handle_new_connections(app->server);
        server_handle_emissions(app->server);
        server_handle_requests(app->server);
    }
}
