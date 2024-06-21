/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** player.c
*/


#include <string.h>
#include "app.h"

static void notify_graphics(server_t *server, bool success,
    vector2u_t *position)
{
    bool sent = controllers_add_emission(server->controllers, CTRL_GRAPHIC,
        "pie %lu %lu %s\n",
        position->x, position->y, success ? "ok" : "ko"
    );

    if (!sent) {
        return log_error("Failed to format incantation end"
            " emission for graphics");
    }
}

static void notify_participant(incantation_t *incantation, bool success,
    player_t *player)
{
    controller_t *controller = (controller_t *) player->controller;
    bool sent = false;

    if (!controller)
        return;
    if (success) {
        sent = controller_add_emission(controller, "Current level: %u\n",
            incantation->level);
    } else {
        sent = controller_add_emission(controller, "ko\n");
    }
    if (!sent) {
        log_error("Failed to notify player %d of incantation end",
            controller->generic.socket
        );
    }
}

static void notify_participants(bool success, incantation_t *incantation)
{
    node_t *node = incantation->players->first;
    player_t *player = NULL;

    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        notify_participant(incantation, success, player);
        node = node->next;
    }
}

static void clear_incantation_requester_request(incantation_t *incantation)
{
    player_t *player = incantation->requester;
    controller_t *controller = player
        ? (controller_t *) player->controller
        : NULL;

    if (controller)
        controller_clear_first_request(controller);
}

void app_handle_world_lifecycle_incantation(world_t *world, server_t *server,
    incantation_t *incantation)
{
    time_unit_t elapsed = chrono_get_elapsed_units(&world->chrono);
    bool success = true;

    incantation->cooldown -= elapsed;
    if (incantation->cooldown > 0)
        return;
    success = incantation_is_valid(incantation, world->map);
    notify_graphics(server, success, &(incantation->location));
    if (success)
        incantation_complete_success(incantation, world->map);
    if (incantation->players->len > 0)
        notify_participants(success, incantation);
    clear_incantation_requester_request(incantation);
    world_remove_incantation(world, incantation);
}

void app_handle_world_lifecycle_incantations(world_t *world, server_t *server)
{
    node_t *node = world->incantations->first;
    node_t *next = NULL;
    incantation_t *incantation = NULL;

    while (node) {
        next = node->next;
        incantation = NODE_TO_PTR(node, incantation_t *);
        app_handle_world_lifecycle_incantation(world, server, incantation);
        node = next;
    }
}
