/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** chrono.c
*/

#include <stdio.h>
#include "types/trantor/chrono.h"

void chrono_start(chrono_t *chrono)
{
    gettimeofday(&chrono->started_at, NULL);
}

void chrono_stop(chrono_t *chrono)
{
    gettimeofday(&chrono->stopped_at, NULL);
}

time_unit_t chrono_get_elapsed_units(chrono_t *chrono)
{
    float sec = (float) (
        chrono->stopped_at.tv_sec - chrono->started_at.tv_sec
    );
    float usec = (float) (
        chrono->stopped_at.tv_usec - chrono->started_at.tv_usec
    );
    float elapsed = sec + (usec / 1000000);

    return elapsed * (float) chrono->frequency;
}

void chrono_units_to_timeval(chrono_t *chrono, time_unit_t units,
    timeval_t *tv)
{
    float total = units / (float) chrono->frequency;
    time_t sec = (time_t) total;
    float usec = (total - (float) sec) * 1000000;

    tv->tv_sec = (time_t) sec;
    tv->tv_usec = (suseconds_t) usec;
}
