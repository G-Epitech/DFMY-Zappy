/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** end.c
*/

#include "types/trantor/world.h"
#include "types/trantor/incantation.h"

bool world_end_incantation(world_t *world, incantation_t *incantation)
{
    if (!incantation_is_valid(incantation, world->map)) {
        world_remove_incantation(world, incantation);
        return false;
    }
    return incantation_complete_success(incantation, world->map);
}
