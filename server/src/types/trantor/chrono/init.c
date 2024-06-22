/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** chrono.c
*/

#include <stdio.h>
#include "types/trantor/chrono.h"

void chrono_init(chrono_t *chrono, size_t frequency)
{
    chrono->started_at = (timeval_t) { 0 };
    chrono->stopped_at = (timeval_t) { 0 };
    chrono->frequency = frequency;
}
