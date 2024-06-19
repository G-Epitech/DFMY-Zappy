/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** start.c
*/

#include "types/world/incantation.h"
#include "types/world/world.h"
#include "types/world/player.h"

static void incantation_add_players_from_cell(incantation_t *incantation,
    map_cell_t *cell)
{
    node_t *node = cell->players->first;
    player_t *player = NULL;

    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        if (player != incantation->requester &&
            player->level == incantation->level) {
            incantation_add_player(incantation, player);
        }
        node = node->next;
    }
}

incantation_t *incantation_start(player_t *player, world_t *world)
{
    incantation_t *incantation = incantation_new(player->level, player);
    map_cell_t *cell = NULL;

    if (!incantation)
        return NULL;
    cell = &MAP_CELL_AT_POS(world->map, player->position);
    incantation_add_players_from_cell(incantation, cell);
    if (!incantation_is_valid(incantation, world->map)) {
        incantation_remove_all_players(incantation);
        incantation_free(incantation);
        return NULL;
    }
    list_push(world->incantations, NODE_DATA_FROM_PTR(incantation));
    return incantation;
}
