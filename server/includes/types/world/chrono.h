/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Clock
*/

#pragma once

#include <stddef.h>
#include <sys/time.h>

// @brief Represent a time unit of Trantor world
typedef float time_unit_t;

typedef struct chrono_s {
    // @brief Starting time of chrono
    struct timeval started_at;
    // @brief Stopped time of chrono
    struct timeval stopped_at;
    // @brief Frequency of world
    size_t frequency;
} chrono_t;

/**
 * @brief Initialize a chrono
 * @param chrono Chrono to initialize
 * @param frequency Frequency of the chrono
 */
void chrono_init(chrono_t *chrono, size_t frequency);
