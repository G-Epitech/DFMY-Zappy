/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** zappy_server.c
*/

#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "app.h"
#include "types/args.h"

void app_setup_sig_handlers(void)
{
    struct termios term = { 0 };

    if (isatty(STDIN_FILENO)) {
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag &= ~(ECHOCTL);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }
    signal(SIGINT, (void (*)(int)) &app_stop);
    signal(SIGTERM, (void (*)(int)) &app_stop);
}

app_t *app_sig_handlers_target(app_t *app, bool set)
{
    static app_t *target = NULL;

    if (set)
        target = app;
    return target;
}

void app_init(app_t *app)
{
    app->running = true;
    app->server = NULL;
    args_init(&app->args);
    app_sig_handlers_target(app, true);
    app_setup_sig_handlers();
}
