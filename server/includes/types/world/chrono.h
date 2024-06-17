/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Clock
*/

#pragma once

#include <stddef.h>
#include <sys/time.h>
#include "time.h"

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

/**
 * @brief Start the chrono
 * @param chrono Chrono to start
 */
void chrono_start(chrono_t *chrono);

/**
 * @brief Stop the chrono
 * @param chrono Chrono to stop
 */
void chrono_stop(chrono_t *chrono);

/**
 * @brief Get the elapsed time of the chrono
 * @param chrono Chrono to get the elapsed time
 * @return Elapsed time units
 */
time_unit_t chrono_get_elapsed_units(chrono_t *chrono);

/**
 * @brief Convert time units to timeval
 * @param chrono Chrono to use for conversion
 * @param units Time units to convert
 * @param tv Timeval to set
 */
void chrono_units_to_timeval(chrono_t *chrono, time_unit_t units,
    timeval_t *tv);
