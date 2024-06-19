/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** complete.c
*/

#include "types/trantor/incantation.h"
#include "types/trantor/player.h"
#include "types/trantor/map.h"

static void increment_player_levels(incantation_t *incantation)
{
    node_t *node = incantation->players->first;
    player_t *player = NULL;

    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        player->level++;
        node = node->next;
    }
}

static void remove_resources(incantation_t *incantation,
    map_t *map)
{
    node_t *node = incantation->players->first;
    player_t *player = NODE_TO_PTR(node, player_t *);
    map_cell_t *cell = MAP_PLAYER_CELL(map, player);
    incantation_requirements_t *req =
            incantation_get_requirements(incantation->level);

    for (resource_t i = RES_FOOD; i < RES_LEN; i++) {
        cell->resources[i] -= req->resources[i];
    }
}

void incantation_complete_success(incantation_t *incantation,
    map_t *map)
{
    increment_player_levels(incantation);
    remove_resources(incantation, map);
}
