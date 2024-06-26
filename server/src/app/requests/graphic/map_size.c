/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include "app.h"

void app_handle_gui_request_map_size(app_t *app, controller_t *controller,
    request_t *request)
{
    map_t *map = app->world->map;
    incoming_token_t token = { 0 };

    if (request_get_token(request, 1, &token)) {
        controller_add_emission(controller, "sbp\n");
        return log_warn("No arguments expected for 'msz' command");
    }
    controller_add_emission(controller, "msz %zu %zu\n", map->size.x,
        map->size.y);
}
