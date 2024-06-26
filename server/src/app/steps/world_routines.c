/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** routines.c
*/

#include "app.h"

void app_handle_world_routines(app_t *app)
{
    if (app->world->paused)
        return;
    app_handle_world_routine_resources_generation(app->world);
    app_handle_world_routine_team_victory(app->world, app->server);
    app_handle_world_routine_map_updates(app->world, app->server);
}
