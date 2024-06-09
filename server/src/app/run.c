/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** zappy_server.c
*/

#include "app.h"
#include "types/args.h"

int app_exit(args_t *args, int code)
{
    args_free(args);
    return code;
}

int app_run(int argc, char **argv)
{
    args_t args = { 0 };

    args_init(&args);
    if (!args_parse(argc, argv, &args) || !args_are_valid(&args))
        return app_exit(&args, APP_EXIT_FAILURE);
    if (args.help) {
        app_print_usage();
        return app_exit(&args, APP_EXIT_SUCCESS);
    }
    return app_exit(&args, APP_EXIT_SUCCESS);
}
