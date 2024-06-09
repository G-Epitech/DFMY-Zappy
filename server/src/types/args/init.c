/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options new
*/

#include "types/args.h"

void args_init(args_t *args)
{
    args->teams = NULL;
    args->width = 0;
    args->height = 0;
    args->clients_nb = 0;
    args->frequency = ARGS_DEFAULT_FREQ;
    args->port = -1;
    args->help = false;
}
