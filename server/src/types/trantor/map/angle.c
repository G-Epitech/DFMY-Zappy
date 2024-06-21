/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** angle.c
*/

#include <stdio.h>
#include <math.h>
#include "types/trantor/map.h"

static void normalize_positions(map_t *map, vector2d_t *delta,
    vector2l_t *dest)
{
    if (fabs(delta->y) > (double)map->size.y / 2) {
        if (delta->y < 0)
            dest->y += (long)map->size.y;
        else
            dest->y -= (long)map->size.y;
    }
    if (fabs(delta->x) > (double)map->size.x / 2) {
        if (delta->x < 0)
            dest->x += (long)map->size.x;
        else
            dest->x -= (long)map->size.x;
    }
}

double map_get_sound_angle(map_t *map, vector2u_t src, vector2u_t dest)
{
    vector2l_t dest_d = { 0 };
    vector2l_t src_d = { 0 };
    vector2d_t delta = { 0 };
    double angle = 0;

    if (!map)
        return -1;
    if (src.x == dest.x && src.y == dest.y)
        return 0;
    src_d = VECTOR2L_FROM_U(src);
    dest_d = VECTOR2L_FROM_U(dest);
    delta.x = (double)dest_d.x - (double)src_d.x;
    delta.y = (double)dest_d.y - (double)src_d.y;
    normalize_positions(map, &delta, &dest_d);
    delta.x = (double)dest_d.x - (double)src_d.x;
    delta.y = (double)dest_d.y - (double)src_d.y;
    angle = atan2(delta.y, delta.x) * 180 / M_PI;
    angle = 180 - angle;
    return angle;
}
