/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options new
*/

#include "types/options/options.h"

void options_init(options_t *options)
{
    options->port = 0;
    options->width = 0;
    options->height = 0;
    options->clients_nb = 0;
    options->freq = 0;
    options->teams = NULL;
}
