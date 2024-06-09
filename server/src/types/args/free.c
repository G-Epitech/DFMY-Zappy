/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options free
*/

#include <stdlib.h>
#include "types/args.h"

void args_free(args_t *args)
{
    if (args->teams != NULL)
        free(args->teams);
}
