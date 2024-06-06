/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options ctor and dtor
*/

#include <stdio.h>
#include <stdlib.h>
#include "options/type.h"

options_t *options_create(void)
{
    options_t *options = malloc(sizeof(options_t));

    if (options == NULL)
        return NULL;
    options->port = -1;
    options->width = -1;
    options->height = -1;
    options->clientsNb = -1;
    options->freq = -1;
    options->teams = NULL;
    return options;
}

void options_destroy(options_t *options)
{
    if (options->teams != NULL)
        free(options->teams);
    free(options);
}
