/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** World free
*/

#include "types/world/team.h"
#include "types/world/player.h"
#include "types/world/world.h"

static void map_cell_free(map_cell_t cell)
{
    if (cell.players)
        list_free(cell.players, NULL);
    if (cell.eggs)
        list_free(cell.eggs, NULL);
}

static void map_free(map_t *map)
{
    for (int i = 0; i < map->size.y; i++) {
        for (int j = 0; j < map->size.x; j++) {
            map_cell_free(map->cells[i][j]);
        }
        free(map->cells[i]);
    }
    free(map);
}

void world_free(world_t *world)
{
    if (!world)
        return;
    if (world->map)
        map_free(world->map);
    if (world->teams)
        list_free(world->teams, (node_freer_t)team_free_as_node_data);
    if (world->players)
        list_free(world->players, (node_freer_t)player_free_as_node_data);
    if (world->incantations)
        list_free(world->incantations, NULL);
    resource_manager_free(world->resources_manager);
    free(world);
}
