/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** player.c
*/


#include "app.h"

void app_handle_world_lifecycle_events_delay(world_t *world, server_t *server)
{
    world_reset_event_delay(world);
    world_update_resources_generation_delay(world);
}
