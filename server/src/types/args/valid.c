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
        return fprintf(stderr, "Missing server port\n") || true;
    if (args->width == 0)
        return fprintf(stderr, "Missing map width\n") || true;
    if (args->height == 0)
        return fprintf(stderr, "Missing map height\n") || true;
    if (args->clients_nb == 0)
        return fprintf(stderr, "Missing clients number\n") || true;
    if (args->teams == NULL)
        return fprintf(stderr, "Missing teams names\n") || true;
    return true;
}
