/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** take.c
*/

#include "types/world/player.h"
#include "types/world/map.h"
#include "types/world/resource.h"

void map_player_set_object(map_t *map, player_t *player, resource_t resource)
{
    map_cell_t cell = {0};

    if (!map || !player)
        return;
    cell = map->cells[player->position.y][player->position.x];
    if (player->inventory[resource] > 0) {
        cell.resources[resource] += 1;
        player->inventory[resource] -= 1;
    }
}
