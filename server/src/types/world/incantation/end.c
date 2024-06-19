/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** end.c
*/

#include "types/world/world.h"
#include "types/world/incantation.h"

static void incantation_increment_player_levels(incantation_t *incantation)
{
    node_t *node = incantation->players->first;
    player_t *player = NULL;

    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        player->level++;
        node = node->next;
    }
}

static void incantation_remove_resources(incantation_t *incantation,
    map_t *map)
{
    node_t *node = incantation->players->first;
    player_t *player = NODE_TO_PTR(node, player_t *);
    vector2u_t *pos = &player->position;
    map_cell_t *cell = MAP_CELL_AT_POS(map, (*pos));
    incantation_requirements_t *req =
            incantation_get_requirements(incantation->level);

    for (resource_t i = RES_FOOD; i < RES_LEN; i++) {
        cell->resources[i] -= req->resources[i];
    }
}

static void incantation_end_success(incantation_t *incantation, map_t *map)
{
    incantation_increment_player_levels(incantation);
    incantation_remove_resources(incantation, map);
}

bool incantation_end(incantation_t *incantation, world_t *world)
{
    if (!incantation_is_valid(incantation, world->map)) {
        incantation_cleanup(incantation, world);
        return false;
    }
    incantation_end_success(incantation, world->map);
    incantation_cleanup(incantation, world);
    return true;
}
