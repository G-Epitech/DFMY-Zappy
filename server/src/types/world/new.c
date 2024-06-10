/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** World new
*/

#include <memory.h>
#include "types/world.h"

static map_cell_t *map_cell_new(void)
{
    map_cell_t *cell = calloc(1, sizeof(map_cell_t));

    if (!cell)
        return NULL;
    cell->eggs = list_new();
    cell->players = list_new();
    memset(cell->resources, 0, RES_LEN * sizeof(size_t));
    return cell;
}

static map_t *map_new(int width, int height)
{
    map_t *map = calloc(1, sizeof(map_t));

    if (!map)
        return NULL;
    map->size.x = width;
    map->size.y = height;
    map->cells = calloc(height, sizeof(map_cell_t *));
    if (!map->cells)
        return NULL;
    for (int i = 0; i < height; i++) {
        map->cells[i] = map_cell_new();
        if (!map->cells[i])
            return NULL;
    }
    return map;
}

world_t *world_new(int width, int height, float frequency)
{
    world_t *world = calloc(1, sizeof(world_t));

    if (!world)
        return NULL;
    world->map = map_new(width, height);
    world->teams = list_new();
    world->players = list_new();
    world->incantations = list_new();
    world->resources_manager = resource_manager_new();
    if (!world->map || !world->teams || !world->players ||
    !world->incantations || !world->resources_manager)
        return NULL;
    world->next_event_delay = 0;
    chrono_init(&world->clock, frequency);
    return world;
}
