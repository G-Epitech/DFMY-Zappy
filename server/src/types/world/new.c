/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** World new
*/

#include "types/world.h"

static map_cell_t *map_cell_new(void)
{
    map_cell_t *cell = calloc(1, sizeof(map_cell_t));

    if (!cell)
        return NULL;
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
        map->cells[i] = calloc(width, sizeof(map_cell_t));
        if (!map->cells[i])
            return NULL;
    }
    return map;
}

world_t *world_new(int width, int height)
{
    world_t *world = calloc(1, sizeof(world_t));

    if (!world)
        return NULL;
    world->map = map_new(width, height);
    if (!world->map)
        return NULL;
    return world;
}
