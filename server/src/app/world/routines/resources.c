/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** resources.c
*/

#include "types/trantor/world.h"
#include "types/trantor/resource.h"

void app_handle_world_routine_resources_generation(world_t *world)
{
    resources_manager_t *resources_manager = &world->map->resources_manager;

    if (resources_manager->next_generation > 0)
        return;
    map_refill_resources(world->map);
    resources_manager->next_generation = RES_MANAGER_NEXT_GENERATION_DELAY;
    world_register_event(world, resources_manager->next_generation);
}
