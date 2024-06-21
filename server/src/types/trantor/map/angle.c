/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** angle.c
*/

#include <math.h>
#include "types/trantor/map.h"

static void normalize_positions(map_t *map, vector2d_t *delta,
    vector2u_t *dest)
{
    if (fabs(delta->y) > map->size.y / 2) {
        if (delta->y < 0)
            dest->y += map->size.y;
        else
            dest->y -= map->size.y;
    }
    if (fabs(delta->x) > map->size.x / 2) {
        if (delta->x < 0)
            dest->x += map->size.x;
        else
            dest->x -= map->size.x;
    }
}

double map_get_sound_angle(map_t *map, vector2u_t src, vector2u_t dest)
{
    vector2d_t delta = { 0 };
    double angle = 0;

    if (!map)
        return -1;
    if (src.x == dest.x && src.y == dest.y)
        return 0;
    delta.x = (double)dest.x - (double)src.x;
    delta.y = (double)dest.y - (double)src.y;
    normalize_positions(map, &delta, &dest);
    delta.x = (double)dest.x - (double)src.x;
    delta.y = (double)dest.y - (double)src.y;
    angle = atan2(delta.y, delta.x) * 180 / M_PI;
    return angle;
}
