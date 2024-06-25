/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** player.c
*/

#include <string.h>
#include "app.h"
#include "types/trantor/egg.h"

static void notify_graphics_of_player_death(server_t *server, player_t *player)
{
    bool sent = controllers_add_emission(server->controllers, CTRL_GRAPHIC,
        "pdi %zu\n", player->id);

    if (!sent) {
        log_error("Failed to emit player death emission to "
            "graphics controllers");
    }
}

static void notify_new_slot(server_t *server, egg_t *egg)
{
    bool success = NULL;

    if (!egg)
        return;
    success = controllers_add_emission(server->controllers, CTRL_GRAPHIC,
        "enw %zu %ld %zu %zu\n",
        egg->id, egg->laid_by, egg->position.x, egg->position.y
    );
    if (!success)
        return log_error("Failed to emit egg hatching message");
}

static void app_handle_player_death(world_t *world, server_t *server,
    player_t *player)
{
    controller_t *controller = (controller_t *) player->controller;
    egg_t *new_slot = NULL;

    notify_graphics_of_player_death(server, player);
    if (CTRL_CAN_EMIT(controller)) {
        controller_add_emission(controller, "dead\n");
        controller->generic.state = CTRL_ALLOW_EMIT;
    } else {
        server_disconnect_controller(server, controller);
    }
    controller->player.type = CTRL_UNKNOWN;
    controller_clear_requests(controller);
    new_slot = world_kill_player(world, player, !CTRL_CAN_EMIT(controller));
    notify_new_slot(server, new_slot);
}

static void app_handle_world_lifecycle_player_lives_and_cooldown(
    world_t *world, server_t *server, player_t *player)
{
    time_unit_t elapsed = chrono_get_elapsed_units(&world->chrono);
    // TODO: remove useless step
    size_t prev_food = player->inventory[RES_FOOD];
    time_unit_t new_lives = player->lives - elapsed;

    if (player->controller) {
        player->controller->cooldown -= elapsed;
        if (player->controller->cooldown <= 0)
            player->controller->cooldown = 0;
        else
            world_register_event(world, player->controller->cooldown);
    }
    player_update_lives(player, new_lives);
    // TODO: remove useless step
    if (prev_food != player->inventory[RES_FOOD]) {
        controllers_add_emission(server->controllers, CTRL_GRAPHIC,
            "pin %zu %zu %zu %zu %zu %zu %zu %zu %zu %zu\n",
            player->id, player->position.x, player->position.y,
            player->inventory[RES_FOOD], player->inventory[RES_LINEMATE],
            player->inventory[RES_DERAUMERE], player->inventory[RES_SIBUR],
            player->inventory[RES_MENDIANE], player->inventory[RES_PHIRAS],
            player->inventory[RES_THYSTAME]
        );
    }
    if (player->lives <= 0 || player->controller->state == CTRL_DISCONNECTED) {
        app_handle_player_death(world, server, player);
    } else {
        world_register_event(world, player->lives);
    }
}

void app_handle_world_lifecycle_players_lives_and_cooldown(world_t *world,
    server_t *server)
{
    node_t *node = world->players->first;
    player_t *player = NULL;
    node_t *next = NULL;

    while (node) {
        next = node->next;
        player = NODE_TO_PTR(node, player_t *);
        app_handle_world_lifecycle_player_lives_and_cooldown(
            world, server, player
        );
        node = next;
    }
}

void app_handle_world_lifecycle_dead_players(world_t *world,
    server_t *server)
{
    node_t *node = world->dead_players->first;
    player_controller_t *controller = NULL;
    player_t *player = NULL;
    node_t *next = NULL;

    while (node) {
        next = node->next;
        player = NODE_TO_PTR(node, player_t *);
        controller = player->controller;
        if (!controller || controller->state == CTRL_DISCONNECTED) {
            list_erase(world->dead_players, node, &player_free_as_node_data);
            continue;
        }
        if (controller->emissions->bytes == 0) {
            server_disconnect_controller(server, (controller_t *) controller);
            list_erase(world->dead_players, node, &player_free_as_node_data);
        }
        node = next;
    }
}

void app_handle_world_lifecycle_players(world_t *world, server_t *server)
{
    app_handle_world_lifecycle_dead_players(world, server);
    app_handle_world_lifecycle_players_lives_and_cooldown(world, server);
}
