/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** verify.c
*/

#include "types/world/incantation.h"
#include "types/world/player.h"
#include "types/world/map.h"

static const incantation_requirements_t incantation_requirements[] = {
    {.nb_players = 1, .resources = {0, 1, 0, 0, 0, 0, 0}},
    {.nb_players = 2, .resources = {0, 1, 1, 1, 0, 0, 0}},
    {.nb_players = 2, .resources = {0, 2, 0, 1, 0, 2, 0}},
    {.nb_players = 4, .resources = {0, 1, 1, 2, 0, 1, 0}},
    {.nb_players = 4, .resources = {0, 1, 2, 1, 3, 0, 0}},
    {.nb_players = 6, .resources = {0, 1, 2, 3, 0, 1, 0}},
    {.nb_players = 6, .resources = {0, 2, 2, 2, 2, 2, 1}},
};

incantation_requirements_t incantation_requirement(unsigned int level)
{
    return incantation_requirements[level - 1];
}

static bool incantation_check_resources(list_t *players,
    const size_t resources[RES_LEN], map_t *map)
{
    player_t *first_player = NODE_TO_PTR(players->first, player_t *);
    map_cell_t *cell = &MAP_CELL_AT_POS(map, first_player->position);

    for (size_t i = 0; i < RES_LEN; i++) {
        if (cell->resources[i] < resources[i])
            return false;
    }
    return true;
}

bool incantation_is_valid(incantation_t *incantation, map_t *map)
{
    incantation_requirements_t requirement = {0};

    if (incantation->level > 7)
        return false;
    requirement = incantation_requirement(incantation->level);
    if (incantation->players->len < requirement.nb_players)
        return false;
    if (!incantation_check_resources(incantation->players,
        requirement.resources, map))
        return false;
    return true;
}