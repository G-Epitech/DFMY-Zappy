/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** register.c
*/

#include "types/world/world.h"
#include "types/world/player.h"
#include "log.h"

bool world_register_player(world_t *world, player_t *player, team_t *team)
{
    if (!team_add_player(team, player))
        return false;
    if (!map_add_player(world->map, player)) {
        team_remove_player(team, player);
        return false;
    }
    if (!list_push(world->players, NODE_DATA_FROM_PTR(player))) {
        world_unregister_player(world, player);
        return false;
    }
    player->id = world->next_player_id;
    world->next_player_id += 1;
    return true;
}

void world_unregister_player(world_t *world, player_t *player)
{
    team_remove_player(player->team, player);
    map_remove_player(world->map, player);
    if (player->incantation)
        incantation_remove_player(player->incantation, player);
}
