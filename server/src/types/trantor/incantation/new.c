/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/trantor/incantation.h"

void incantation_init(incantation_t *incantation, unsigned int level)
{
    incantation->level = level;
    incantation->cooldown = INCANTATION_DURATION;
}

incantation_t *incantation_new(unsigned int level)
{
    incantation_t *incantation = calloc(1, sizeof(incantation_t));

    if (!incantation)
        return NULL;
    incantation->players = list_new();
    if (!incantation->players) {
        incantation_free(incantation);
        return NULL;
    }
    incantation_init(incantation, level);
    return incantation;
}
