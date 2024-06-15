/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** stop.c
*/

#include <signal.h>
#include "app.h"

void app_setup_sig_handlers(void)
{
    signal(SIGINT, (void (*)(int)) &app_stop);
    signal(SIGTERM, (void (*)(int)) &app_stop);
}

bool *app_stopped(void)
{
    static bool stopped = false;

    return &stopped;
}

int app_exit(app_t *app, int code)
{
    if (app->server)
        server_free(app->server);
    args_free(&app->args);
    return code;
}

void app_stop(void)
{
    *app_stopped() = true;
}
