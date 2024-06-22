/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** server.c
*/

#include "app.h"

timeval_t *app_get_timeout(app_t *app, timeval_t *timeout)
{
    if (app->server->controllers->len == 0 ||
        app->world->next_event_delay < 0) {
        return NULL;
    }
    chrono_units_to_timeval(&app->world->chrono,
            app->world->next_event_delay, timeout);
    return timeout;
}

void app_handle_server_connections(app_t *app)
{
    timeval_t timeout = { 0, 0 };
    timeval_t *timeout_ptr = app_get_timeout(app, &timeout);
    int res;

    server_remove_disconnected_controllers(app->server);
    chrono_start(&app->world->chrono);
    res = server_poll_all_controllers(app->server, timeout_ptr);
    chrono_stop(&app->world->chrono);
    if (res > 0) {
        server_handle_new_connections(app->server);
        server_handle_emissions(app->server);
        server_handle_requests(app->server);
    }
}
