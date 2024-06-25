/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** quadrant.c
*/

#include "types/direction.h"

static const direction_quadrant_t direction_quadrants[] = {
    {.direction = DIR_NORTH, .quadrants = {3, 4, 5, 6, 7, 8, 1, 2}},
    {.direction = DIR_EAST, .quadrants = {1, 2, 3, 4, 5, 6, 7, 8}},
    {.direction = DIR_SOUTH, .quadrants = {7, 8, 1, 2, 3, 4, 5, 6}},
    {.direction = DIR_WEST, .quadrants = {5, 6, 7, 8, 1, 2, 3, 4}},
};

int direction_get_quadrant(direction_t direction, int quadrant)
{
    if (quadrant == -1 || quadrant > 7)
        return (-1);
    return (direction_quadrants[direction - 1].quadrants[quadrant]);
}
