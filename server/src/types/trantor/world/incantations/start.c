/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** start.c
*/

#include "types/trantor/incantation.h"
#include "types/trantor/world.h"
#include "types/trantor/player.h"

incantation_t *world_start_incantation(world_t *world, player_t *player)
{
    incantation_t *incantation = incantation_new(player->level + 1);
    map_cell_t *cell = NULL;

    if (!incantation)
        return NULL;
    cell = MAP_PLAYER_CELL(world->map, player);
    if (!incantation_add_players_from_cell(incantation, cell) ||
        !incantation_is_valid(incantation, world->map) ||
        !list_push(world->incantations, NODE_DATA_FROM_PTR(incantation))) {
        incantation_remove_all_players(incantation);
        incantation_free(incantation);
        return NULL;
    }
    incantation->requester = player;
    return incantation;
}
