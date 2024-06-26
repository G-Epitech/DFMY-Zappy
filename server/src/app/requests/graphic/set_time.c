/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include <string.h>
#include "app.h"

static bool parse_frequency(request_token_t *token, size_t *frequency)
{
    char str_token[32] = { 0 };
    char *end_ptr = NULL;

    if (token->size >= 32)
        return false;
    memcpy(str_token, token->content, token->size);
    *frequency = strtoul(str_token, &end_ptr, 10);
    return end_ptr != &str_token[0];
}

static bool handle_arguments(controller_t *controller, request_t *request,
    size_t *frequency)
{
    request_token_t token = { 0 };

    if (request_get_token(request, 2, &token)) {
        controller_add_emission(controller, "sbp\n");
        log_warn("Too many arguments for 'sst' command");
        return false;
    }
    if (!request_get_token(request, 1, &token)) {
        controller_add_emission(controller, "sbp\n");
        log_warn("Not enough arguments for 'sst' command");
        return false;
    }
    if (!parse_frequency(&token, frequency)) {
        controller_add_emission(controller, "sbp\n");
        log_warn("Invalid frequency value for 'sst' command");
        return false;
    }
    return true;
}

void app_handle_gui_request_set_time_unit(app_t *app, controller_t *controller,
    request_t *request)
{
    size_t frequency = 0;

    if (!handle_arguments(controller, request, &frequency))
        return;
    if (frequency > APP_MAX_FREQ) {
        controller_add_emission(controller, "sbp\n");
        return log_warn("Invalid frequency value for 'sst' command");
    }
    if (frequency > 0) {
        app->world->chrono.frequency = frequency;
        app->world->paused = false;
    } else {
        app->world->paused = true;
    }
    controller_add_emission(controller, "sst %zu\n",
        app->world->paused ? 0 : app->world->chrono.frequency);
    controllers_add_emission(app->server->controllers, CTRL_GRAPHIC,
        "sgt %zu\n", app->world->paused ? 0 : app->world->chrono.frequency);
}
