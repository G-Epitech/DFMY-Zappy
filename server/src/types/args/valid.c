/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** valid.c
*/

#include <stdio.h>
#include <string.h>
#include "types/args.h"

static bool are_valid_teams(char **teams)
{
    size_t i = 0;

    if (!teams)
        return fprintf(stderr, "Missing teams names\n") && false;
    while (teams[i]) {
        if (strcmp(teams[i], "GRAPHIC") == 0)
            return fprintf(stderr, "Illegal team name: GRAPHIC\n") && false;
        i += 1;
    }
    return true;
}

bool args_are_valid(args_t *args)
{
    if (args->help)
        return true;
    if (args->port < 0)
        return fprintf(stderr, "Missing server port\n") && false;
    if (args->width == 0)
        return fprintf(stderr, "Missing map width\n") && false;
    if (args->height == 0)
        return fprintf(stderr, "Missing map height\n") && false;
    if (args->clients_nb == 0)
        return fprintf(stderr, "Missing clients number\n") && false;
    if (!are_valid_teams(args->teams))
        return false;
    return true;
}
