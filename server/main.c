/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** main.c
*/

#include <stdio.h>
#include "options/options.h"

static void print_server_options(options_t *options)
{
    printf("Port: %d\n", options->port);
    printf("Width: %d\n", options->width);
    printf("Height: %d\n", options->height);
    printf("ClientsNb: %d\n", options->clientsNb);
    printf("Freq: %d\n", options->freq);
    if (options->teams == NULL)
        return;
    for (int i = 0; options->teams[i] != NULL; i++) {
        printf("Team %d: %s\n", i, options->teams[i]);
    }
}

int main(int ac, char **av)
{
    options_t *options = options_parse(ac, av);

    if (options == NULL) {
        print_usage();
        return 84;
    }
    print_server_options(options);
    options_destroy(options);
    return 0;
}
