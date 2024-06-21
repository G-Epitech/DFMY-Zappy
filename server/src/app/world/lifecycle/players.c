/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** player.c
*/

#include <string.h>
#include "app.h"

static void notify_graphics_of_player_death(server_t *server, player_t *player)
{
    bool sent = controllers_add_emission(server->controllers, CTRL_GRAPHIC,
        "pdi %zu\n", player->id);

    if (!sent) {
        log_error("Failed to emit player death emission to "
            "graphics controllers");
    }
}


static void app_handle_player_death(world_t *world, server_t *server,
    player_t *player)
{
    controller_t *controller = (controller_t *) player->controller;

    notify_graphics_of_player_death(server, player);
    if (CTRL_CAN_EMIT(controller)) {
        controller_add_emission(controller, "dead\n");
        world_kill_player(world, player, false);
        controller->generic.state = CTRL_ALLOW_EMIT;
    } else if (controller->generic.state != CTRL_DISCONNECTED) {
        server_disconnect_controller(server, controller);
        world_kill_player(world, player, true);
    }
}

static void app_handle_world_lifecycle_player_lives(world_t *world,
    server_t *server, player_t *player)
{
    time_unit_t elapsed = chrono_get_elapsed_units(&world->chrono);
    time_unit_t new_lives = player->lives - elapsed;

    player_update_lives(player, new_lives);
    if (player->lives <= 0 || player->controller->state == CTRL_DISCONNECTED) {
        app_handle_player_death(world, server, player);
    } else {
        world_register_event(world, player->lives);
    }
}

void app_handle_world_lifecycle_players_lives(world_t *world,
    server_t *server)
{
    node_t *node = world->players->first;
    player_t *player = NULL;
    node_t *next = NULL;

    while (node) {
        next = node->next;
        player = NODE_TO_PTR(node, player_t *);
        app_handle_world_lifecycle_player_lives(world, server, player);
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
    app_handle_world_lifecycle_players_lives(world, server);
}
