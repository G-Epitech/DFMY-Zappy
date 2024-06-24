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
    incantation_requirements_t *req =
            incantation_get_requirements(incantation->level);

    for (resource_t res = RES_FOOD; res < RES_LEN; res++) {
        map_remove_resource(map, player->position, res, req->resources[res]);
    }
}

bool incantation_complete_success(incantation_t *incantation,
    map_t *map)
{
    if (!incantation || !map || !incantation->players->first)
        return false;
    increment_player_levels(incantation);
    remove_resources(incantation, map);
    return true;
}
