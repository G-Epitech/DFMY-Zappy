/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** World free
*/

#include "types/trantor/world.h"
#include "types/trantor/player.h"

bool world_add_player(world_t *world, player_t *player)
{
    node_data_t data = NODE_DATA_FROM_PTR(player);
    list_t *lists_stack[] = {
            world->players,
            world->map->cells[player->position.y][player->position.x].players,
            player->team->players,
    };

    for (size_t i = 0; i < sizeof(lists_stack) / sizeof(lists_stack[0]); i++) {
        if (!list_push(lists_stack[i], data))
            return false;
    }
    world_player_register(world, player);
    return true;
}
