/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** zappy_server.c
*/

#include "app.h"
#include "types/args.h"

int app_run(app_t *app)
{
    while (app->running) {
        timeval_t timeout = {10, 0};

        if (server_poll(app->server, &timeout) > 0) {
            server_handle_new_connections(app->server);
            server_handle_emissions(app->server);
            server_handle_requests(app->server);
        }
    }
    server_close_all_connections(app->server);
    log_info("Server gracefully shutting down");
    return app_exit(app, APP_EXIT_SUCCESS);
}
