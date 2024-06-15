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
    while (app->running);
    log_info("Server gracefully shutting down");
    return app_exit(app, APP_EXIT_SUCCESS);
}
