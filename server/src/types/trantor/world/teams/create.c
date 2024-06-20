/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** create.c
*/

#include "types/trantor/world.h"

bool world_create_team(world_t *world, char *team_name, size_t min_slots)
{
    team_t *team = team_new(team_name, min_slots);

    if (!team)
        return false;
    if (world_ensure_team_slots(world, team) != min_slots ||
        !list_push(world->teams, NODE_DATA_FROM_PTR(team))
    ) {
        team_free(team);
        return false;
    }
    return true;
}

bool world_create_teams(world_t *world, char **teams_names, size_t min_slots)
{
    size_t i = 0;

    while (teams_names[i]) {
        if (!world_create_team(world, teams_names[i], min_slots))
            break;
        i += 1;
    }
    if (teams_names[i])
        list_clear(world->teams, &team_free_as_node_data);
    return teams_names[i] == NULL;
}
