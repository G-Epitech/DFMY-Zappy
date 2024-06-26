/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** forward.c
*/

#include <string.h>
#include "app.h"
#include "types/trantor/egg.h"

static void emit_cell_stats(controller_t *controller, map_cell_t *cell)
{
    size_t tokens = 0;

    for (resource_t i = RES_FOOD; i < RES_LEN; i++) {
        for (size_t j = 0; j < cell->resources[i]; j++) {
            controller_add_emission(controller, "%s%s",
                (tokens++ ? " " : ""), resource_to_string(i));
        }
    }
    for (size_t i = 0; i < cell->players->len; i++) {
        controller_add_emission(controller, "%splayer",
            (tokens++ ? " " : ""));
    }
    for (size_t i = 0; i < cell->eggs->len; i++)
        controller_add_emission(controller, "%segg", (tokens++ ? " " : ""));
    controller_add_emission_raw(controller, ",", 1);
}

static void look_axis_vertical(player_t *player, map_t *map,
    vector2l_t *look_vector)
{
    controller_t *controller = (controller_t *) player->controller;
    vector2l_t look_position = VECTOR2L_FROM_U(player->position);
    vector2u_t real_look_position;
    size_t wing_size = 1;
    map_cell_t *cell = NULL;

    for (size_t i = 0; i < player->level; i++) {
        wing_size += 2;
        look_position.y += look_vector->y;
        look_position.x -= (((long) wing_size - 1) / 2) * look_vector->x;
        for (size_t j = 0; j < wing_size; j++) {
            real_look_position = map_resolve_position(map, look_position);
            cell = MAP_CELL_AT_POS(map, real_look_position);
            emit_cell_stats(controller, cell);
            look_position.x += look_vector->x;
        }
        look_position.x = (long) player->position.x;
    }
}

static void look_axis_horizontal(player_t *player, map_t *map,
    vector2l_t *look_vector)
{
    controller_t *controller = (controller_t *) player->controller;
    vector2l_t look_position = VECTOR2L_FROM_U(player->position);
    vector2u_t real_look_position;
    size_t wing_size = 1;
    map_cell_t *cell = NULL;

    for (size_t i = 0; i < player->level; i++) {
        wing_size += 2;
        look_position.x += look_vector->x;
        look_position.y -= (((long) wing_size - 1) / 2) * look_vector->y;
        for (size_t j = 0; j < wing_size; j++) {
            real_look_position = map_resolve_position(map, look_position);
            cell = MAP_CELL_AT_POS(map, real_look_position);
            emit_cell_stats(controller, cell);
            look_position.y += look_vector->y;
        }
        look_position.y = (long) player->position.y;
    }
}

bool app_handle_player_request_look_onstart(
    __attribute_maybe_unused__ app_t *app,
    __attribute_maybe_unused__ player_controller_t *controller,
    request_t *request)
{
    incoming_token_t token = { 0 };

    if (request_get_token(request, 1, &token)) {
        log_warn("No arguments expected for 'Look' command");
        return false;
    }
    return true;
}

void app_handle_player_request_look_onfinish(
    app_t *app,
    player_controller_t *controller,
    __attribute_maybe_unused__ request_t *request)
{
    player_t *player = controller->player;
    vector2l_t vector = { 0 };
    axis_t axis = player_get_look_axis(player);
    map_cell_t *cell = MAP_PLAYER_CELL(app->world->map, player);

    player_get_look_vector(player, &vector);
    controller_add_emission_raw((controller_t *) controller, "[", 1);
    emit_cell_stats((controller_t *) controller, cell);
    if (axis == AXIS_V)
        look_axis_vertical(player, app->world->map, &vector);
    else
        look_axis_horizontal(player, app->world->map, &vector);
    controller_add_emission_raw((controller_t *) controller, "]\n", 2);
}
