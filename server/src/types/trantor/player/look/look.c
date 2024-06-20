/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** look.c
*/

#include <string.h>
#include "types/trantor/player.h"
#include "types/trantor/map.h"

char *player_look(player_t *player, map_t *map)
{
    player_look_info_t look_info = { 0 };
    size_t nb_cells = player->level * player->level;
    map_cell_stats_t *cell_stats = calloc(nb_cells, sizeof(map_cell_stats_t));
    char *res = NULL;

    if (cell_stats == NULL || map == NULL)
        return NULL;
    player_look_vector(player, &look_info);
    map_cell_get_stats(MAP_PLAYER_CELL(map, player), &cell_stats[0]);
    look_info.buf_size += map_cell_stats_str_len(&cell_stats[0]);
    player_look_axis(player, map, &look_info, cell_stats);
    res = map_cells_stats_string(cell_stats, nb_cells, look_info.buf_size);
    free(cell_stats);
    return res;
}
