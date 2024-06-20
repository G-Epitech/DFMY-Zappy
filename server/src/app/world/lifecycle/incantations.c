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
    emission_params_t params = { 0 };
    bool created = emission_params_from_format(&params, EMISSION_COMPLETE,
        "pie %lu %lu %s",
        position->x, position->y, success ? "ok" : "ko"
    );

    if (!created ||
        !controllers_add_emission(server->controllers, &params, CTRL_GRAPHIC)
    ) {
        return log_error("Failed to format incantation end"
            " emission for graphics");
    }
}

static bool get_participants_notification(incantation_t *incantation,
    smart_ptr_t **buffer_ptr, size_t *buffer_size, bool success)
{
    char *buffer = NULL;
    ssize_t size = -1;

    if (success) {
        size = my_asprintf(&buffer, "Current level: %u", incantation->level);
    } else {
        buffer = strdup("ko");
        size = 2;
    }
    *buffer_ptr = buffer ? smart_ptr_new(buffer) : NULL;
    *buffer_size = *buffer_ptr ? size : 0;
    return *buffer_ptr != NULL;
}

static void notify_participant(smart_ptr_t *buffer_ptr, size_t buffer_size,
    player_t *player)
{
    controller_t *controller = (controller_t *) player->controller;

    if (!controller)
        return;
    if (!controller_add_emission_from_shared_buffer(controller, buffer_ptr,
        buffer_size, EMISSION_COMPLETE)
    ) {
        log_error("Failed to notify player %d of incantation end",
            controller->generic.socket
        );
    }
}

static void notify_participants(server_t *server, bool success,
    incantation_t *incantation)
{
    node_t *node = incantation->players->first;
    player_t *player = NULL;
    smart_ptr_t *buffer_ptr = NULL;
    size_t buffer_size = 0;

    if (!get_participants_notification(incantation, &buffer_ptr,
        &buffer_size, success)
    ) {
        return log_error("Failed to format incantation end"
            " emission for participants");
    }
    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        notify_participant(buffer_ptr, buffer_size, player);
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
        notify_participants(server, success, incantation);
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
