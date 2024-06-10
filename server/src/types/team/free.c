/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Team free
*/

#include "types/team.h"

void team_free(team_t *team)
{
    if (team) {
        free(team->name);
        list_free(team->players, NULL);
        list_free(team->eggs, NULL);
        free(team);
    }
}

void team_free_as_node_data(void *data)
{
    team_free((team_t *)data);
}
