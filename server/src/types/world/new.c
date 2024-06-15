/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** World new
*/

#include <memory.h>
#include "types/world/world.h"

void world_init(world_t *world, size_t frequency)
{
    chrono_init(&world->chrono, frequency);
    resources_manager_init(&world->resources_manager, world->map->size);
    world->next_event_delay = 0.0f;
}

world_t *world_new(vector2u_t map_size, size_t frequency)
{
    world_t *world = calloc(1, sizeof(world_t));

    if (!world)
        return NULL;
    world->map = map_new(map_size);
    world->teams = list_new();
    world->players = list_new();
    world->incantations = list_new();
    if (!world->map || !world->teams || !world->players ||
        !world->incantations) {
        world_free(world);
        return NULL;
    }
    world_init(world, frequency);
    return world;
}
