/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include "app.h"

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
