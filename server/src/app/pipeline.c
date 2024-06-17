/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** pipeline.c
*/

#include "app.h"

// @brief Application steps
static const app_step_t app_pipeline[] = {*
    &app_handle_server_logic
};

// @brief Application steps size
static const size_t app_pipeline_size =
    sizeof(app_pipeline) / sizeof(app_step_t);

void app_run_pipeline(app_t *app)
{
    size_t i = 0;

    while (i < app_pipeline_size && app->running) {
        app_pipeline[i](app);
        i += 1;
    }
}
