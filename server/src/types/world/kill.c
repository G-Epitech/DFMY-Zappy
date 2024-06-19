/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** remove.c
*/

#include "types/world/world.h"
#include "types/world/player.h"
#include "types/world/incantation.h"

void world_kill_player(world_t *world, player_t *player, bool zombie)
{
    node_t *node = list_find(world->players, NODE_DATA_FROM_PTR(player));

    world_unregister_player(world, player);
    if (!node)
        return;
    if (!zombie) {
        list_pop(world->players, node);
        list_append(world->dead_players, node);
    } else {
        list_erase(world->players, node, &player_free_as_node_data);
    }
}
