/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** delay.c
*/

#include "types/trantor/world.h"

void world_start_game(world_t *world)
{
    gettimeofday(&world->start_time, NULL);
}

void world_end_game(world_t *world)
{
    gettimeofday(&world->end_time, NULL);
}

void world_get_game_duration(world_t *world, timeval_t *duration)
{
    timersub(&world->end_time, &world->start_time, duration);
}
