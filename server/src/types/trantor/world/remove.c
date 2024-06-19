/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** remove.c
*/

#include "types/trantor/world.h"
#include "types/trantor/player.h"
#include "types/trantor/incantation.h"

void world_remove_player(world_t *world, player_t *player)
{
    node_data_t data = NODE_DATA_FROM_PTR(player);
    node_t *node = NULL;
    list_t *lists_stack[] = {
            world->players,
            world->map->cells[player->position.y][player->position.x].players,
            player->team->players,
    };

    for (size_t i = 0; i < sizeof(lists_stack) / sizeof(lists_stack[0]); i++) {
        node = list_find(lists_stack[i], data);
        if (node)
            list_erase(lists_stack[i], node, NULL);
    }
    if (player->incantation)
        incantation_remove_player(player->incantation, player);
}
