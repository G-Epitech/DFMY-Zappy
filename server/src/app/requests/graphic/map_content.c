/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include <string.h>
#include "app.h"

static bool parse_coordinate(request_token_t *token, size_t *coordinate)
{
    char str_token[32] = { 0 };
    char *end_ptr = NULL;

    if (token->size >= 32)
        return false;
    memcpy(str_token, token->content, token->size);
    *coordinate = strtoul(str_token, &end_ptr, 10);
    return end_ptr != &str_token[0];
}

static bool parse_cell_position(request_token_t tokens[2],
    vector2u_t *position)
{
    if (!parse_coordinate(&tokens[0], &position->x))
        return false;
    if (!parse_coordinate(&tokens[1], &position->y))
        return false;
    return true;
}

static void send_cell_content(controller_t *controller,
    map_t *map, vector2u_t *position)
{
    map_cell_t *cell = MAP_CELL_AT_POS(map, *position);

    controller_add_emission(controller,
        "bct %zu %zu %zu %zu %zu %zu %zu %zu %zu\n",
        position->x, position->y, cell->resources[RES_FOOD],
        cell->resources[RES_LINEMATE], cell->resources[RES_DERAUMERE],
        cell->resources[RES_SIBUR], cell->resources[RES_MENDIANE],
        cell->resources[RES_PHIRAS], cell->resources[RES_THYSTAME]
    );
}

void app_handle_gui_request_map_content(app_t *app, controller_t *controller,
    request_t *request)
{
    map_t *map = app->world->map;
    vector2u_t position = { 0 };
    request_token_t token = { 0 };

    if (request_get_token(request, 1, &token)) {
        controller_add_emission(controller, "sbp\n");
        return log_warn("No arguments expected for 'mct' command");
    }
    for (position.y = 0; position.y < map->size.y; position.y++) {
        for (position.x = 0; position.x < map->size.x; position.x++) {
            send_cell_content(controller, map, &position);
        }
    }
}

void app_handle_gui_request_map_cell_content(app_t *app,
    controller_t *controller, request_t *request)
{
    request_token_t tokens[2] = { 0 };
    vector2u_t position = { 0 };

    if (request_get_token(request, 3, &tokens[0])) {
        controller_add_emission(controller, "sbp\n");
        return log_warn("Too many arguments for 'bct' command");
    }
    if (!request_get_token(request, 1, &tokens[0]) ||
        !request_get_token(request, 2, &tokens[1])) {
        controller_add_emission(controller, "sbp\n");
        return log_warn("Too few arguments for 'bct' command");
    }
    if (!parse_cell_position(tokens, &position) ||
        MAP_OUT_POSITION(app->world->map, position)
    ) {
        controller_add_emission(controller, "sbp\n");
        return log_warn("Invalid arguments for 'bct' command");
    }
    send_cell_content(controller, app->world->map, &position);
}
