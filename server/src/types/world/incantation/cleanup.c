/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** cleanup.c
*/

#include "types/world/world.h"
#include "types/world/incantation.h"

void incantation_cleanup(incantation_t *incantation, world_t *world)
{
    node_t *node = NULL;

    incantation_remove_all_players(incantation);
    node = list_find(world->incantations, NODE_DATA_FROM_PTR(incantation));
    if (node)
        list_erase(world->incantations, node, &incantation_free_as_node_data);
}
