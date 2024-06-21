/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** remove.c
*/

#include "types/trantor/world.h"
#include "types/trantor/egg.h"

void world_kill_egg(world_t *world, egg_t *egg)
{
    map_remove_egg(world->map, egg);
    team_remove_egg(egg->team, egg);
}

static void notify_graphics_egg_death(list_t *controllers, egg_t *egg)
{
    emission_params_t params = { 0 };

    if (emission_params_from_format(&params, EMISSION_COMPLETE,
        "edi %ld\n", egg->id)) {
        controllers_add_emission(controllers, &params, CTRL_GRAPHIC);
    }
}

void world_kill_eggs(world_t *world, list_t *eggs, server_t *server)
{
    node_t *node = eggs->first;
    egg_t *egg = NULL;

    while (node) {
        egg = NODE_TO_PTR(node, egg_t *);
        notify_graphics_egg_death(server->controllers, egg);
        world_kill_egg(world, egg);
    }
}
