/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options free
*/

#include <stdlib.h>
#include "types/options/options.h"

void options_free(options_t *options)
{
    if (options->teams != NULL)
        free(options->teams);
}
