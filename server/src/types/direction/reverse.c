/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** reverse.c
*/

#include "types/direction.h"

direction_t direction_reverse(direction_t direction)
{
    switch (direction) {
        case DIR_NORTH:
            return DIR_SOUTH;
        case DIR_SOUTH:
            return DIR_NORTH;
        case DIR_WEST:
            return DIR_EAST;
        default:
            return DIR_WEST;
    }
}
