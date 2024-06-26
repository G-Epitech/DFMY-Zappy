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
    request_token_t token = { 0 };

    request_get_token(request, 0, &token);
    if (token.size == STR_STRICT_SIZEOF("GRAPHIC") &&
        memcmp(token.content, "GRAPHIC", token.size) == 0
    ) {
        app_try_promote_controller_to_graphic(app, controller);
        request->status = REQ_FINISHED;
        return;
    }
    if (app->world->winner)
        controller_add_emission_raw(controller, "ko\n", 3);
    else {
        app_try_promote_controller_to_player(app, controller, request,
            token.size);
    }
    request->status = REQ_FINISHED;
}
