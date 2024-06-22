/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** math.c
*/

#include <math.h>
#include "types/trantor/player.h"

static const player_direction_quadrant_t g_direction_quadrant[] = {
    {.direction = DIR_NORTH, .quadrants = {7, 8, 1, 2, 3, 4, 5, 6}},
    {.direction = DIR_EAST, .quadrants = {5, 6, 7, 8, 1, 2, 3, 4}},
    {.direction = DIR_SOUTH, .quadrants = {3, 4, 5, 6, 7, 8, 1, 2}},
    {.direction = DIR_WEST, .quadrants = {1, 2, 3, 4, 5, 6, 7, 8}},
};

int angle_to_quadrant(double angle)
{
    if (angle == -1)
        return (-1);
    return ((int) round(angle / 45));
}

int quandrant_normalize_with_direction(int quadrant, int direction)
{
    if (quadrant == -1)
        return (-1);
    return (g_direction_quadrant[direction - 1].quadrants[quadrant]);
}
