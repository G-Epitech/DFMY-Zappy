/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options parser
*/

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include "options/options.h"

void print_usage(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height");
    printf(" -n team1 team2 ... -c clientsNb -f freq\n");
    printf("option description\n");
    printf("-p port        port number (1024 <-> 65535)\n");
    printf("-x width       width of the world (10 <-> 30)\n");
    printf("-y height      height of the world (10 <-> 30)\n");
    printf("-n [teams]     name of the team (at least one)\n");
    printf("-c clientsNb   number of authorized clients per team");
    printf(" (1 <-> 200)\n");
    printf("-f freq        reciprocal of time unit for");
    printf(" execution of actions (2 <-> 10000)\n");
}

static void fill_teams(options_t *options, int argc, char **argv)
{
    int i = 0;

    optind--;
    options->teams = malloc(sizeof(char *) * (argc - optind + 1));
    if (options->teams == NULL)
        return;
    for (; optind < argc && argv[optind][0] != '-'; i++) {
        options->teams[i] = argv[optind];
        optind++;
    }
    options->teams[i] = NULL;
}

static void fill_int_options(int opt, options_t *options)
{
    switch (opt) {
        case 'p':
            options->port = atoi(optarg);
            break;
        case 'x':
            options->width = atoi(optarg);
            break;
        case 'y':
            options->height = atoi(optarg);
            break;
        case 'c':
            options->clientsNb = atoi(optarg);
            break;
        case 'f':
            options->freq = atoi(optarg);
            break;
        default:
            return;
    }
}

static bool options_are_valid(options_t *options)
{
    if (options->port < 1024 || options->port > 65535)
        return false;
    if (options->width < 10 || options->width > 30)
        return false;
    if (options->height < 10 || options->height > 30)
        return false;
    if (options->clientsNb < 1 || options->clientsNb > 200)
        return false;
    if (options->freq < 2 || options->freq > 10000)
        return false;
    if (options->teams == NULL)
        return false;
    return true;
}

options_t *options_parse(int argc, char **argv)
{
    options_t *options = options_create();
    int opt = 0;

    if (options == NULL)
        return NULL;
    opt = getopt(argc, argv, "p:x:y:n:c:f:");
    while (opt != -1) {
        fill_int_options(opt, options);
        if (opt == 'n')
            fill_teams(options, argc, argv);
        opt = getopt(argc, argv, "p:x:y:n:c:f:");
    }
    if (!options_are_valid(options)) {
        options_destroy(options);
        return NULL;
    }
    return options;
}
