/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** update_delay.c
*/

#include "types/trantor/world.h"

void world_update_resources_generation_delay(world_t *world)
{
    time_unit_t elapsed = chrono_get_elapsed_units(&world->chrono);

    world->resources_manager.next_generation -= elapsed;
    if (world->resources_manager.next_generation <= 0)
        world->resources_manager.next_generation = 0;
    world_register_event(world, world->resources_manager.next_generation);
}
