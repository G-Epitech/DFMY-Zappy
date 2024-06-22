/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** handler.c
*/

#include <string.h>
#include "app.h"

void app_handle_graphic_request(app_t *app, controller_t *controller,
    request_t *request)
{
    request->status = REQ_FINISHED;
}
