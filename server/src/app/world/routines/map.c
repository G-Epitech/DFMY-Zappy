/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** resources.c
*/

#include <stdio.h>
#include "types/trantor/world.h"
#include "types/trantor/resource.h"

static void handle_cell_changes(world_t *world, server_t *server,
    vector2u_t *position)
{
    map_cell_t *cell = MAP_CELL_AT_POS(world->map, *position);
    char message[1024] = { 0 };
    int len;

    if (!cell->changed)
        return;
    len = snprintf(message, sizeof(message),
        "bct %zu %zu %zu %zu %zu %zu %zu %zu %zu\n",
        position->x, position->y, cell->resources[RES_FOOD],
        cell->resources[RES_LINEMATE], cell->resources[RES_DERAUMERE],
        cell->resources[RES_SIBUR], cell->resources[RES_MENDIANE],
        cell->resources[RES_PHIRAS], cell->resources[RES_THYSTAME]
    );
    controllers_add_emission_raw(server->controllers, CTRL_GRAPHIC,
        message, len);
    map_mark_cell_as_up_to_date(world->map, cell);
}

void app_handle_world_routine_map_updates(world_t *world, server_t *server)
{
    vector2u_t pos = { 0, 0 };

    if (world->map->cells_changed == 0)
        return;
    for (pos.x = 0; pos.x < world->map->size.x; pos.x++) {
        for (pos.y = 0; pos.y < world->map->size.y; pos.y++) {
            handle_cell_changes(world, server, &pos);
        }
    }
}
