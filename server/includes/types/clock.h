/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Clock
*/

#pragma once

#include <sys/time.h>

// @brief Represent a time unit of Trantor world
typedef float time_unit_t;

typedef struct clock_s {
    // @brief Starting time of clock
    struct timeval started_at;
    // @brief Stopped time of clock
    struct timeval stopped_at;
    // @brief Frequency of world
    float frequency;
} clock_t;
