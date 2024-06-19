/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** cleanup.c
*/

#include "types/trantor/world.h"
#include "types/trantor/incantation.h"

void world_remove_incantation(world_t *world, incantation_t *incantation)
{
    node_t *node = NULL;

    incantation_remove_all_players(incantation);
    node = list_find(world->incantations, NODE_DATA_FROM_PTR(incantation));
    if (node)
        list_erase(world->incantations, node, &incantation_free_as_node_data);
}
