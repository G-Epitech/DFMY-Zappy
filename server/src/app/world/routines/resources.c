/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** resources.c
*/

#include "types/world/world.h"
#include "types/world/resource.h"

static void world_routine_generate_resource(map_t *map,
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

void world_routine_resources_generation(world_t *world)
{
    resources_manager_t *resource_manager = NULL;

    if (world->resources_manager.next_generation > 0.0f)
        return;
    resource_manager = &world->resources_manager;
    for (int i = 0; i < RES_LEN; i++) {
        if (resource_manager->stats[i].actual <
            resource_manager->stats[i].limit) {
            world_routine_generate_resource(world->map, resource_manager,
                (resource_t)i);
        }
    }
    resource_manager->next_generation += RES_MANAGER_NEXT_GENERATION_DELAY;
}
