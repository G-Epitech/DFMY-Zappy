/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** player.c
*/


#include "app.h"

void app_handle_world_lifecycle_game_starting(world_t *world,
    server_t *server)
{
    if (server->controllers->len > 0 && world->start_time.tv_sec < 0)
        world_start_game(world);
}
