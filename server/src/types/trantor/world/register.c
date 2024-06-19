/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** register.c
*/

#include "types/trantor/world.h"
#include "types/trantor/player.h"

void world_player_register(world_t *world, player_t *player)
{
    player->id = world->next_player_id;
    world->next_player_id += 1;
}
