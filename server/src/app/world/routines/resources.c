/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** resources.c
*/

#include "types/trantor/world.h"
#include "types/trantor/resource.h"

static void generate_resource(map_t *map,
    resources_manager_t *resources_manager, resource_t type)
{
    size_t quantity = resources_manager->stats[type].limit -
        resources_manager->stats[type].actual;
    vector2u_t pos = {0, 0};

    for (size_t i = 0; i < quantity; i++) {
        vector2u_random(&pos, &map->size);
        map->cells[pos.y][pos.x].resources[type] += 1;
    }
    resources_manager->stats[type].actual += quantity;
}

void app_handle_world_routine_resources_generation(world_t *world)
{
    resources_manager_t *resource_manager = &world->resources_manager;
    resource_stat_t *stats = resource_manager->stats;

    if (world->resources_manager.next_generation > 0.0f)
        return;
    for (resource_t res = 0; res < RES_LEN; res++) {
        if (stats[res].actual < stats[res].limit)
            generate_resource(world->map, resource_manager, res);
    }
    resource_manager->next_generation = RES_MANAGER_NEXT_GENERATION_DELAY;
}
