/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** remove.c
*/

#include "types/trantor/world.h"
#include "types/trantor/egg.h"

void world_kill_egg(world_t *world, egg_t *egg)
{
    map_remove_egg(world->map, egg);
    team_remove_egg(egg->team, egg);
}
