/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** server.c
*/

#include "app.h"

void app_handle_world_lifecycle(app_t *app)
{
    app_handle_world_lifecycle_players(app->server, app->world);
}
