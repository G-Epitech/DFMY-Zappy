/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** axis.c
*/

#include <string.h>
#include "types/trantor/resource.h"
#include "types/trantor/player.h"
#include "types/trantor/map.h"

static void player_look_axis_vertical(player_t *player, map_t *map,
    player_look_info_t *info, map_cell_stats_t *cell_stats)
{
    vector2l_t look_position = VECTOR2L_FROM_U(player->position);
    vector2u_t real_look_position;
    size_t wing_size = 1;
    map_cell_t *cell = NULL;
    size_t cell_cnt = 1;

    for (size_t i = 1; i < player->level; i++) {
        wing_size += 2;
        look_position.y += info->vector.y;
        look_position.x -= (((long)wing_size - 1) / 2) * info->vector.x;
        for (size_t j = 0; j < wing_size; j++) {
            real_look_position = map_resolve_position(map, look_position);
            cell = MAP_CELL_AT_POS(map, real_look_position);
            map_cell_get_stats(cell, &cell_stats[cell_cnt]);
            info->buf_size += map_cell_stats_str_len(&cell_stats[cell_cnt]);
            cell_cnt++;
            look_position.x += info->vector.x;
        }
        look_position.x = (long)player->position.x;
    }
}

static void player_look_axis_horizontal(player_t *player, map_t *map,
    player_look_info_t *info, map_cell_stats_t *cell_stats)
{
    vector2l_t look_position = VECTOR2L_FROM_U(player->position);
    vector2u_t real_look_position;
    size_t wing_size = 1;
    map_cell_t *cell = NULL;
    size_t cell_cnt = 1;

    for (size_t i = 1; i < player->level; i++) {
        wing_size += 2;
        look_position.x += info->vector.x;
        look_position.y -= (((long)wing_size - 1) / 2) * info->vector.y;
        for (size_t j = 0; j < wing_size; j++) {
            real_look_position = map_resolve_position(map, look_position);
            cell = MAP_CELL_AT_POS(map, real_look_position);
            map_cell_get_stats(cell, &cell_stats[cell_cnt]);
            info->buf_size += map_cell_stats_str_len(&cell_stats[cell_cnt]);
            cell_cnt++;
            look_position.y += info->vector.y;
        }
        look_position.y = (long)player->position.y;
    }
}

void player_look_axis(player_t *player, map_t *map, player_look_info_t *info,
    map_cell_stats_t *cell_stats)
{
    if (player->direction == DIR_NORTH || player->direction == DIR_SOUTH)
        player_look_axis_vertical(player, map, info, cell_stats);
    else
        player_look_axis_horizontal(player, map, info, cell_stats);
}
