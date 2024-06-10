/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Clock
*/

#pragma once

#include <sys/time.h>

typedef float time_unit_t;

typedef struct clock_s {
    struct timeval started_at;
    struct timeval stopped_at;
    float frequency;
} clock_t;
