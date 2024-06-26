/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** usage.c
*/

#include <stdio.h>

static const char *app_usage_lines[] = {
    "USAGE: ./zappy_server -p port -x width -y height"
    " -n team1 team2 ... -c clients_nb",
    "ARGUMENTS:",
    "  -p, --port [0, 65535]                           port number of server",
    "  -x, --width [1, +inf]                           width of the world",
    "  -y, --height [1, +inf]                          height of the world",
    "  -n, --teams [...teams]                          names of the teams "
    "(at least one)",
    "  -c, --clients-nb [1, 200]                       number of authorized"
    "  clients per team",
    "OPTIONS:",
    "  -h, --help                                      display this help"
    " and exit",
    "  -f, --frequency [0, 10000]                      reciprocal of time"
    " unit for execution of actions",
    "  -v, --verbose [DEBUG,  INFO, WARNING, ERROR]   set verbose level",
    NULL
};

void app_print_usage(void)
{
    size_t i = 0;

    while (app_usage_lines[i] != NULL) {
        printf("%s\n", app_usage_lines[i]);
        i += 1;
    }
}
