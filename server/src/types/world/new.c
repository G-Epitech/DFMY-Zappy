/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** World new
*/

#include <memory.h>
#include "types/world/world.h"

static bool map_cell_init(map_cell_t *cell)
{
    cell->eggs = list_new();
    cell->players = list_new();
    if (!cell->eggs || !cell->players)
        return false;
    memset(cell->resources, 0, RES_LEN * sizeof(size_t));
    return true;
}

static bool map_cell_init_row(map_cell_t *row, int width)
{
    for (int i = 0; i < width; i++) {
        if (!map_cell_init(&row[i]))
            return false;
    }
    return true;
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
        map->cells[i] = calloc(width, sizeof(map_cell_t));
        if (!map->cells[i])
            return NULL;
        if (!map_cell_init_row(map->cells[i], width))
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
    world->next_event_delay = 0.0f;
    chrono_init(&world->clock, frequency);
    return world;
}
