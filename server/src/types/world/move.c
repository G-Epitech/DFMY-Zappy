/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Player
*/

#include "types/world/player.h"
#include "types/world/world.h"

static void increment_player_position(world_t *world, player_t *player)
{
    switch (player->direction) {
        case DIR_NORTH:
            player->position.y = (player->position.y + 1) % world->map->size.y;
            break;
        case DIR_EAST:
            player->position.x = (player->position.x + 1) % world->map->size.x;
            break;
        case DIR_SOUTH:
            player->position.y = (player->position.y - 1) % world->map->size.y;
            break;
        case DIR_WEST:
            player->position.x = (player->position.x - 1) % world->map->size.x;
            break;
    }
}

void world_forward_player(world_t *world, player_t *player)
{
    node_t *node = NULL;
    map_cell_t cell;

    if (!world || !player)
        return;
    cell = world->map->cells[player->position.y][player->position.x];
    node = list_find(cell.players, NODE_DATA_FROM_PTR(player));
    if (node)
        list_erase(cell.players, node, NULL);
    increment_player_position(world, player);
}
