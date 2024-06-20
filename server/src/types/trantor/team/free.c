/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Team free
*/

#include "types/trantor/team.h"
#include "types/trantor/egg.h"

void team_free(team_t *team)
{
    if (!team)
        return;
    free(team->name);
    list_free(team->players, NULL);
    list_free(team->eggs, &egg_free_as_node_data);
    free(team);
}

void team_free_as_node_data(node_data_t data)
{
    team_free(NODE_DATA_TO_PTR(data, team_t *));
}
