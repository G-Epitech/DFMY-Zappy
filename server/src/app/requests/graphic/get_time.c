/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include "app.h"

void app_handle_gui_request_get_time_unit(app_t *app, controller_t *controller,
    request_t *request)
{
    request_token_t token = { 0 };

    if (request_get_token(request, 1, &token)) {
        controller_add_emission(controller, "sbp\n");
        return log_warn("No arguments expected for 'sgt' command");
    }
    controller_add_emission(controller, "sgt %zu\n",
        app->world->chrono.frequency
    );
}
