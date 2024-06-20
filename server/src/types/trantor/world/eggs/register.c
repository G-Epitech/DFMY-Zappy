/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** eggs.c
*/

#include "types/trantor/world.h"
#include "types/trantor/egg.h"

egg_t *world_add_egg(world_t *world, team_t *team)
{
    egg_t *egg = egg_new();

    if (!egg)
        return NULL;
    if (!team_add_egg(team, egg) || !map_add_egg(world->map, egg)) {
        world_kill_egg(world, egg);
        return NULL;
    }
    egg->id = world->next_egg_id;
    world->next_egg_id += 1;
    return egg;
}
