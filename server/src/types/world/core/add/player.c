/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/world/world.h"
#include "types/world/player.h"

bool world_add_player(world_t *world, player_t *player)
{
    node_data_t data = NODE_DATA_FROM_PTR(player);
    map_cell_t cell;

    if (!list_push(world->players, data))
        return false;
    cell = world->map->cells[player->position.y][player->position.x];
    if (!list_push(cell.players, data))
        return false;
    if (!list_push(player->team->players, data))
        return false;
    return true;
}
