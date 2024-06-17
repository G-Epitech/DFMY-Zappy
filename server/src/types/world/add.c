/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** World free
*/

#include "types/world/world.h"
#include "types/world/player.h"

bool world_add_player(world_t *world, player_t *player)
{
    node_data_t data = NODE_DATA_FROM_PTR(player);
    list_t *lists_stack[] = {
            world->players,
            world->map->cells[player->position.y][player->position.x].players,
            player->team->players,
            NULL
    };

    for (int i = 0; lists_stack[i]; i++) {
        if (!list_push(lists_stack[i], data))
            return false;
    }
    return true;
}
