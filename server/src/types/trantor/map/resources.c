/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** resources.c
*/

#include "types/trantor/map.h"
#include "log.h"

static void generate_resource(map_t *map,
    resources_manager_t *resources_manager, resource_t type)
{
    size_t quantity = resources_manager->stats[type].limit -
        resources_manager->stats[type].actual;
    vector2u_t pos = {0, 0};

    for (size_t i = 0; i < quantity; i++) {
        vector2u_random(&pos, &map->size);
        map_add_resource(map, pos, type, 1);
    }
}

void map_refill_resources(map_t *map)
{
    resources_manager_t *resources_manager = &map->resources_manager;
    resource_stat_t *stats = resources_manager->stats;

    for (resource_t res = 0; res < RES_LEN; res++) {
        if (stats[res].actual < stats[res].limit)
            generate_resource(map, resources_manager, res);
    }
}
