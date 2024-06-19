/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** position.c
*/

#include "types/vector2.h"

vector2u_t map_resolve_position(vector2i_t pos, vector2u_t *map_size)
{
    vector2u_t resolved_pos = { 0, 0 };

    pos.x = pos.x % (long)map_size->x;
    pos.y = pos.y % (long)map_size->y;
    if (pos.x < 0)
        resolved_pos.x = map_size->x + pos.x;
    else
        resolved_pos.x = pos.x;
    if (pos.y < 0)
        resolved_pos.y = map_size->y + pos.y;
    else
        resolved_pos.y = pos.y;
    return resolved_pos;
}
