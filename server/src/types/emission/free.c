/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** free.c
*/

#include <stdlib.h>
#include "types/emission.h"

void emission_free(emission_t *emission)
{
    if (!emission)
        return;
    free(emission->buffer);
    free(emission);
}
