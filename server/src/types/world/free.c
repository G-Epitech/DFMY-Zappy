/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** World free
*/

#include "types/world/team.h"
#include "types/world/player.h"
#include "types/world/world.h"
#include "types/world/incantation.h"

void world_free(world_t *world)
{
    if (!world)
        return;
    map_free(world->map);
    list_free(world->teams, &team_free_as_node_data);
    list_free(world->players, &player_free_as_node_data);
    list_free(world->incantations, &incantation_free_as_node_data);
    free(world);
}
