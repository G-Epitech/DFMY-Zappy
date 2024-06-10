/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/world/incantation.h"

void incantation_init(incantation_t *incantation,
    player_controller_t *requester, unsigned int level)
{
    incantation->requester = requester;
    incantation->level = level;
}

incantation_t *incantation_new(player_controller_t *requester,
    unsigned int level)
{
    incantation_t *incantation = calloc(1, sizeof(incantation_t));

    if (!incantation)
        return NULL;
    incantation->players = list_new();
    if (!incantation->players) {
        incantation_free(incantation);
        return NULL;
    }
    incantation_init(incantation, requester, level);
    return incantation;
}
