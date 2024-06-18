/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** zappy_server.c
*/

#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include "app.h"
#include "types/args.h"

void app_setup_sig_handlers(void)
{
    struct termios term = { 0 };
    struct sigaction sa = {
        .sa_handler = (void (*)(int)) &app_stop,
        .sa_flags = SA_RESTART
    };

    if (isatty(STDIN_FILENO)) {
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag &= ~(ECHOCTL);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaction(SIGINT, &sa, NULL);
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
    app->world = NULL;
    args_init(&app->args);
    app_sig_handlers_target(app, true);
    app_setup_sig_handlers();
}
