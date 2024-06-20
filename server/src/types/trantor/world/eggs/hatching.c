/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** hatching.cpp
*/

#include "types/trantor/egg.h"
#include "types/trantor/player.h"
#include "types/trantor/world.h"

player_t *world_hatch_egg(world_t *world, egg_t *egg)
{
    player_t *player = world ? player_new(world->next_player_id) : NULL;

    if (!egg || !player)
        return NULL;
    player->position = egg->position;
    if (!world_register_player(world, player, egg->team)) {
        player_free(player);
        return NULL;
    }
    world->next_player_id += 1;
    return player;
}
