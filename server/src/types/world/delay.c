/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** delay.c
*/

#include "types/world/world.h"

void world_register_event(world_t *world, time_unit_t event_delay)
{
    if (world->next_event_delay == 0.0f)
        world->next_event_delay = event_delay;
    if (world->next_event_delay > event_delay)
        world->next_event_delay = event_delay;
}
