/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options parser
*/

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "options/options.h"

void print_usage(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height");
    printf(" -n name1 name2 ... -c clientsNb -f freq\n");
    printf("option description\n");
    printf("-p port      port number\n");
    printf("-x width     width of the world\n");
    printf("-y height    height of the world\n");
    printf("-n name1 name2 ...  name of the team\n");
    printf("-c clientsNb number of authorized clients per team\n");
    printf("-f freq      ");
    printf("reciprocal of time unit for execution of actions\n");
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

options_t *parse_options(int argc, char **argv)
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
    return options;
}
