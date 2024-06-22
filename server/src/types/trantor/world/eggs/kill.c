/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** remove.c
*/

#include "types/trantor/world.h"
#include "types/trantor/egg.h"
#include "log.h"

void world_kill_egg(world_t *world, egg_t *egg)
{
    map_remove_egg(world->map, egg);
    team_remove_egg(egg->team, egg);
}

static void notify_graphics_egg_death(list_t *controllers, egg_t *egg)
{
    if (!controllers_add_emission(controllers, CTRL_GRAPHIC, "edi %zu\n",
        egg->id)) {
        log_error("Failed to notify graphics of egg death (egg id: %zu)",
            egg->id);
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
        node = node->next;
    }
}
