/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** zappy_server.c
*/

#include <stdio.h>
#include "app.h"
#include "types/args.h"

void app_init(app_t *app)
{
    *app_stopped() = false;
    app->server = NULL;
    args_init(&app->args);
}
