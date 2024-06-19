/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** server.c
*/

#include "app.h"

bool app_handle_timeout(app_t *app, timeval_t *timeout)
{
    if (app->server->controllers->len == 0)
        return false;
    chrono_units_to_timeval(&app->world->chrono,
        app->world->next_event_delay, timeout);
    return true;
}

// TODO: handle timeout
void app_handle_server_connections(app_t *app)
{
    timeval_t timeout = { 0, 0 };
    timeval_t *timeout_ptr = app_handle_timeout(app, &timeout)
        ? &timeout
        : NULL;

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    timeout_ptr = &timeout;
    server_remove_disconnected_controllers(app->server);
    if (server_poll(app->server, timeout_ptr) > 0) {
        server_handle_new_connections(app->server);
        server_handle_emissions(app->server);
        server_handle_requests(app->server);
    }
}
