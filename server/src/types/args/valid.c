/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** valid.c
*/

#include <stdio.h>
#include "types/args.h"

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
    if (args->teams == NULL)
        return fprintf(stderr, "Missing teams names\n") && false;
    return true;
}
