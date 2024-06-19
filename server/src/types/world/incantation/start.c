/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** start.c
*/

#include "types/world/incantation.h"
#include "types/world/world.h"
#include "types/world/player.h"

bool incantation_start(player_t *player, world_t *world)
{
    map_cell_t *cell = &MAP_CELL_AT_POS(world->map, player->position);
    incantation_t *incantation = incantation_new(cell, player->level);

    if (!incantation)
        return false;
    if (!incantation_is_valid(incantation, world->map))
        return false;
    return true;
}
