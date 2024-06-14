/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Team new
*/

#include <string.h>
#include "types/world/team.h"

team_t *team_new(char *name, size_t min_slots)
{
    team_t *team = calloc(1, sizeof(team_t));

    if (!team)
        return NULL;
    team->min_slots = min_slots;
    team->name = strdup(name);
    team->players = list_new();
    team->eggs = list_new();
    if (!team->players || !team->eggs || !team->name) {
        team_free(team);
        return NULL;
    }
    return team;
}
