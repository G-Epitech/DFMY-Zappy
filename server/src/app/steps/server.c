/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** server.c
*/

#include "app.h"

void app_handle_timeout(app_t *app, timeval_t *timeout)
{
    if (app->server->controllers->len == 0 ||
        app->world->next_event_delay == -1) {
        timeout = NULL;
    } else {
        chrono_units_to_timeval(&app->world->chrono,
            app->world->next_event_delay, timeout);
    }
}

void app_handle_server_connections(app_t *app)
{
    timeval_t timeout = { 0, 0 };

    app_handle_timeout(app, &timeout);
    if (server_poll(app->server, &timeout) > 0) {
        server_handle_new_connections(app->server);
        server_handle_emissions(app->server);
        server_handle_requests(app->server);
    }
}
