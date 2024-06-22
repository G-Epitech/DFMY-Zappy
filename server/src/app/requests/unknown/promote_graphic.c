/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** promote_graphic.c
*/

#include "app.h"

void app_promote_controller_to_graphic(app_t *app, controller_t *controller)
{
    bool promoted = controller_graphic_from_generic(controller,
        app->world->map);

    if (!promoted) {
        log_error("Controller on socket %d could not be promoted to graphic."
          " Disconnecting.", controller->generic.socket);
        server_disconnect_controller(app->server, controller);
    } else {
        log_info("Controller on socket %d has been promoted to graphic."
             " Emissions buffer smartly resized to %zu bytes.",
             controller->generic.socket, controller->graphic.emissions->size);
    }
}
