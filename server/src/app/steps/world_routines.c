/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** routines.c
*/

#include "app.h"

void app_handle_world_routines(app_t *app)
{
    world_routine_resources_generation(app->world);
    world_routine_team_victory(app->world, app->server->controllers);
}
