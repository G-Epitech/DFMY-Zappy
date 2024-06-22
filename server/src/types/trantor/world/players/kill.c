/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** remove.c
*/

#include "types/trantor/world.h"
#include "types/trantor/player.h"
#include "types/trantor/incantation.h"

egg_t *world_kill_player(world_t *world, player_t *player, bool zombie)
{
    node_t *node = list_find(world->players, NODE_DATA_FROM_PTR(player));
    team_t *team = player->team;

    world_unregister_player(world, player);
    if (!node)
        return NULL;
    if (!zombie) {
        list_pop(world->players, node);
        list_append(world->dead_players, node);
    } else {
        list_erase(world->players, node, &player_free_as_node_data);
    }
    return world_add_egg_if_needed(world, team);
}
