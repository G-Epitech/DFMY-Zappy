/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Resource manager new
*/

#include <math.h>
#include "types/world/resource.h"

static const float resources_limits[RES_LEN] = {
    [RES_FOOD] = RES_FOOD_DENSITY,
    [RES_LINEMATE] = RES_LINEMATE_DENSITY,
    [RES_DERAUMERE] = RES_DERAUMERE_DENSITY,
    [RES_SIBUR] = RES_SIBUR_DENSITY,
    [RES_MENDIANE] = RES_MENDIANE_DENSITY,
    [RES_PHIRAS] = RES_PHIRAS_DENSITY,
    [RES_THYSTAME] = RES_THYSTAME_DENSITY
};

static size_t get_resource_limit(resource_t resource, vector2u_t map_size)
{
    return (size_t) ceilf((float)
        (map_size.x * map_size.y)
        * resources_limits[resource]
    );
}

void resources_manager_init(resources_manager_t *manager, vector2u_t map_size)
{
    manager->next_generation = RES_MANAGER_NEXT_GENERATION_DELAY;
    for (int i = 0; i < RES_LEN; i++) {
        manager->stats[i].actual = 0;
        manager->stats[i].limit = get_resource_limit(i, map_size);
    }
}
