/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** remove.c
*/

#include "types/world/world.h"
#include "types/world/player.h"
#include "types/world/incantation.h"

static void world_remove_player_from_incantations(world_t *world,
                                                  player_t *player)
{
    node_data_t data = NODE_DATA_FROM_PTR(player);
    node_t *node = world->incantations->first;
    node_t *tmp = NULL;
    incantation_t *incantation = NULL;

    while (node) {
        incantation = NODE_DATA_TO_PTR(node->data, incantation_t *);
        tmp = list_find(incantation->players, data);
        if (tmp) {
            list_erase(incantation->players, tmp, NULL);
        }
        node = node->next;
    }
}

void world_remove_player(world_t *world, player_t *player)
{
    node_data_t data = NODE_DATA_FROM_PTR(player);
    node_t *node = NULL;
    list_t *lists_stack[] = {
            world->players,
            world->map->cells[player->position.y][player->position.x].players,
            player->team->players,
            NULL
    };

    for (int i = 0; lists_stack[i]; i++) {
        node = list_find(lists_stack[i], data);
        if (node)
            list_erase(lists_stack[i], node, NULL);
    }
    world_remove_player_from_incantations(world, player);
}

