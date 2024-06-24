/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** forward.c
*/

#include "app.h"
#include "types/trantor/egg.h"

static void notify_and_move_players(app_t *app, map_cell_t *cell,
    direction_t direction, vector2u_t *destination)
{
    node_t *node = cell->players->first;
    player_t *player = NULL;
    direction_t incoming_direction = direction_reverse(direction);

    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        controller_add_emission((controller_t *) player->controller,
            "eject %d\n", incoming_direction);
        map_move_player_node(app->world->map, node, destination);
        node = node->next;
    }
}

static void notify_graphics_ejection(server_t *server, player_t *player)
{
    controllers_add_emission(server->controllers, CTRL_GRAPHIC,
        "pex %zu\n", player->id);
}

static void lay_egg_if_needed_for_team(app_t *app, team_t *team)
{
    egg_t *egg = world_add_egg_if_needed(app->world, team);

    while (egg) {
        controllers_add_emission(app->server->controllers, CTRL_GRAPHIC,
            "enw %zu %zu %zu %zu\n", egg->id, egg->laid_by,
            egg->position.x, egg->position.y);
        egg = world_add_egg_if_needed(app->world, team);
    }
}

static void kill_eggs_and_notify_graphics(app_t *app, vector2u_t *position)
{
    map_cell_t *cell = MAP_CELL_AT_POS(app->world->map, *position);
    team_t *team = NULL;
    node_t *node = cell->eggs->first;
    node_t *next = NULL;
    egg_t *egg = NULL;

    while (node) {
        next = node->next;
        egg = NODE_TO_PTR(node, egg_t *);
        controllers_add_emission_raw(app->server->controllers, CTRL_GRAPHIC,
            "edi %zu\n", egg->id);
        team = egg->team;
        world_kill_egg(app->world, egg);
        lay_egg_if_needed_for_team(app, team);
        node = next;
    }
}

bool app_handle_player_request_eject_onstart(
    __attribute_maybe_unused__ app_t *app,
    __attribute_maybe_unused__ player_controller_t *controller,
    request_t *request)
{
    request_token_t token = { 0 };

    if (request_get_token(request, 1, &token)) {
        log_warn("No arguments expected for 'Eject' command");
        return false;
    }
    return true;
}

void app_handle_player_request_eject_onfinish(app_t *app,
    player_controller_t *controller,
    __attribute_maybe_unused__ request_t *request)
{
    player_t *player = controller->player;
    vector2u_t destination = player->position;
    map_cell_t *cell = MAP_PLAYER_CELL(app->world->map, player);

    map_forward_position(app->world->map, &destination, player->direction);
    map_move_player(app->world->map, player, &destination);
    notify_and_move_players(app, cell, player->direction, &destination);
    notify_graphics_ejection(app->server, player);
    kill_eggs_and_notify_graphics(app, &destination);
    controller_add_emission((controller_t *) controller, "ok\n");
}
