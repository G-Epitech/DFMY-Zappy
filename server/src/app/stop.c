/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** stop.c
*/

#include <stdio.h>
#include "app.h"

int app_exit(app_t *app, int code)
{
    if (app->server)
        server_free(app->server);
    if (app->world)
        world_free(app->world);
    app_sig_handlers_target(NULL, true);
    args_free(&app->args);
    return code;
}

void app_stop(void)
{
    app_t *app = app_sig_handlers_target(NULL, false);

    if (app)
        app->running = false;
}
