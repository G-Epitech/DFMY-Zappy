/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** math.c
*/

#include <math.h>

int angle_to_quadrant(double angle)
{
    if (angle == -1)
        return (-1);
    return ((int) round(angle / 45)) % 8;
}
