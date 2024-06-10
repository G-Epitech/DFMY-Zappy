/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** chrono.c
*/

#include "types/world/chrono.h"

void chrono_init(chrono_t *chrono, size_t frequency)
{
    chrono->started_at = (struct timeval){0};
    chrono->stopped_at = (struct timeval){0};
    chrono->frequency = frequency;
}
