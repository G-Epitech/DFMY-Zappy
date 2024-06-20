/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** slots.c
*/

#include "types/trantor/world.h"

// TODO: Use this code to generate minimal eggs
/*size_t world_ensure_team_slots(world_t *world, team_t *team)
{
    size_t current = team->players->len + team->eggs->len;

    if (current >= team->min_slots)
        return 0;
    for (size_t i = current; i < team->min_slots; i++) {
        if (!world_add_egg(world, team))
            return i - current;
    }
    return team->min_slots - current;
}*/
