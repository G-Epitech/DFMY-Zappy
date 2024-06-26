/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** server.c
*/

#include "app.h"

void app_handle_world_lifecycle(app_t *app)
{
    app_handle_world_lifecycle_game_starting(app->world, app->server);
    app_handle_world_lifecycle_events_delay(app->world, app->server);
    app_handle_world_lifecycle_players(app->world, app->server);
    app_handle_world_lifecycle_incantations(app->world, app->server);
}
