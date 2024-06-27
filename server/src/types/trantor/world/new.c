/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** World new
*/

#include "types/trantor/world.h"
#include "types/trantor/team.h"

void world_init(world_t *world, size_t frequency)
{
    if (frequency == 0) {
        world->paused = true;
        frequency = WORLD_DEFAULT_FREQ;
    }
    chrono_init(&world->chrono, frequency);
    map_refill_resources(world->map);
    world->next_event_delay = -1;
    world->next_player_id = 0;
    world->next_egg_id = 0;
    world->winner = NULL;
    world->start_time = (timeval_t) { -1, -1 };
    world->end_time = (timeval_t) { -1, -1 };
    world->paused = false;
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
    world->dead_players = list_new();
    if (!world->map || !world->teams || !world->players ||
        !world->incantations || !world->dead_players
    ) {
        world_free(world);
        return NULL;
    }
    world_init(world, frequency);
    return world;
}
