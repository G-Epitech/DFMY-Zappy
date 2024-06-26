/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** eggs.c
*/

#include "types/trantor/world.h"
#include "types/trantor/egg.h"

egg_t *world_add_egg(world_t *world, team_t *team, player_t *player)
{
    long laid_by = player ? (long) player->id : -1;
    egg_t *egg = egg_new(laid_by, world->next_egg_id);
    vector2u_t position = player ? player->position : (vector2u_t) { 0, 0 };

    if (!egg)
        return NULL;
    if (!player)
        vector2u_random(&position, &world->map->size);
    if (!team_add_egg(team, egg) ||
        !map_add_egg(world->map, egg, &position)
    ) {
        world_kill_egg(world, egg);
        return NULL;
    }
    world->next_egg_id += 1;
    return egg;
}

egg_t *world_add_egg_if_needed(world_t *world, team_t *team)
{
    size_t current = team->players->len + team->eggs->len;

    if (current >= team->min_slots)
        return NULL;
    return world_add_egg(world, team, NULL);
}
