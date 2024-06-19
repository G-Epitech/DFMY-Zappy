/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** end.c
*/

#include "types/trantor/world.h"
#include "types/trantor/incantation.h"

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
    vector2u_t *pos = &player->position;
    map_cell_t *cell = MAP_CELL_AT_POS(map, (*pos));
    incantation_requirements_t *req =
            incantation_get_requirements(incantation->level);

    for (resource_t i = RES_FOOD; i < RES_LEN; i++) {
        cell->resources[i] -= req->resources[i];
    }
}

static void end_success(incantation_t *incantation,
    map_t *map)
{
    increment_player_levels(incantation);
    remove_resources(incantation, map);
}

bool world_end_incantation(world_t *world, incantation_t *incantation)
{
    if (!incantation_is_valid(incantation, world->map)) {
        world_remove_incantation(world, incantation);
        return false;
    }
    end_success(incantation, world->map);
    world_remove_incantation(world, incantation);
    return true;
}
