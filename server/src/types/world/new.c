/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** World new
*/

#include "types/world/world.h"
#include "types/world/team.h"

void world_init(world_t *world, size_t frequency)
{
    chrono_init(&world->chrono, frequency);
    resources_manager_init(&world->resources_manager, world->map->size);
    world->next_event_delay = -1.0f;
    world->next_player_id = 0;
}

bool world_create_teams(world_t *world, char **teams_names, size_t min_slots)
{
    size_t i = 0;
    team_t *team = NULL;

    while (teams_names[i]) {
        team = team_new(teams_names[i], min_slots);
        if (!team || !list_push(world->teams, NODE_DATA_FROM_PTR(team))) {
            team_free(team);
            break;
        }
        i += 1;
    }
    if (teams_names[i])
        list_clear(world->teams, &team_free_as_node_data);
    return teams_names[i] == NULL;
}

world_t *world_new(vector2u_t map_size, size_t frequency)
{
    world_t *world = calloc(1, sizeof(world_t));

    if (!world)
        return NULL;
    world->map = map_new(map_size);
    world->teams = list_new();
    world->players = list_new();
    world->incantations = list_new();
    if (!world->map || !world->teams || !world->players ||
        !world->incantations) {
        world_free(world);
        return NULL;
    }
    world_init(world, frequency);
    return world;
}
