/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** position.c
*/

#include "types/trantor/map.h"
#include "types/vector2.h"

vector2u_t map_resolve_position(map_t *map, vector2l_t pos)
{
    vector2u_t resolved_pos = { 0, 0 };

    pos.x = pos.x % (long)map->size.x;
    pos.y = pos.y % (long)map->size.y;
    if (pos.x < 0)
        resolved_pos.x = map->size.x + pos.x;
    else
        resolved_pos.x = pos.x;
    if (pos.y < 0)
        resolved_pos.y = map->size.y + pos.y;
    else
        resolved_pos.y = pos.y;
    return resolved_pos;
}

void map_forward_position(map_t *map, vector2u_t *position,
    direction_t direction)
{
    vector2l_t move_vector = direction_get_move_vector(direction);
    vector2l_t new_pos = { 0, 0 };

    new_pos.x = (long)position->x + move_vector.x;
    new_pos.y = (long)position->y + move_vector.y;
    *position = map_resolve_position(map, new_pos);
}
