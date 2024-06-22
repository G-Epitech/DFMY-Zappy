/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** handler.c
*/

#include <string.h>
#include <stdio.h>
#include "app.h"

void app_handle_unknown_request(app_t *app, controller_t *controller,
    request_t *request)
{
    size_t token_size = request_get_first_token_size(request);

    if (token_size == STR_STRICT_SIZEOF("GRAPHIC") &&
        memcmp(request->buffer, "GRAPHIC", token_size) == 0
    ) {
        app_try_promote_controller_to_graphic(app, controller);
    } else {
        app_try_promote_controller_to_player(app, controller, request,
            token_size);
    }
    request->status = REQ_FINISHED;
}
