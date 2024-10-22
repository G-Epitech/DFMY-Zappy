/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** zappy_server.c
*/

#include <stdio.h>
#include "app.h"
#include "types/args.h"
#include "types/vector2.h"

bool app_create_world(app_t *app)
{
    vector2u_t map_size = { app->args.width, app->args.height };

    app->world = world_new(map_size, app->args.frequency);
    if (!app->world)
        return fprintf(stderr, "Failed to create world\n") && false;
    if (!world_create_teams(app->world, app->args.teams,
        app->args.clients_nb)
    ) {
        world_free(app->world);
        return fprintf(stderr, "Failed to create teams\n") && false;
    }
    return true;
}

bool app_create_and_start_server(app_t *app)
{
    app->server = server_new();
    if (!app->server)
        return fprintf(stderr, "Failed to create server\n") && false;
    if (!server_start(app->server, app->args.port))
        return false;
    log_info("Server started on port %ld", app->args.port);
    return true;
}

int app_start(int argc, char **argv)
{
    app_t app = { 0 };

    app_init(&app);
    if (!args_parse(argc, argv, &app.args) || !args_are_valid(&app.args))
        return app_exit(&app, APP_EXIT_FAILURE);
    if (app.args.help) {
        app_print_usage();
        return app_exit(&app, APP_EXIT_SUCCESS);
    }
    *log_level() = app.args.verbose_level;
    if (!app_create_and_start_server(&app) || !app_create_world(&app))
        return app_exit(&app, APP_EXIT_FAILURE);
    return app_run(&app);
}
