/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** look.c
*/

#include <stdio.h>
#include "types/trantor/resource.h"
#include "types/trantor/player.h"
#include "types/trantor/map.h"

static void get_look_vector(vector2l_t *look_vector,
    player_direction_t player_direction)
{
    switch (player_direction) {
        case DIR_NORTH:
            look_vector->x = 1;
            look_vector->y = 1;
            break;
        case DIR_EAST:
            look_vector->x = 1;
            look_vector->y = -1;
            break;
        case DIR_SOUTH:
            look_vector->x = -1;
            look_vector->y = -1;
            break;
        default:
            look_vector->x = -1;
            look_vector->y = 1;
            break;
    }
}

static size_t cell_stats_buf_size(map_cell_stats_t stats)
{
    size_t buf_size = 0;

    for (resource_t i = RES_FOOD; i < RES_LEN; i++)
        if (stats.resources[i] > 0)
            buf_size += (stats.resources[i] * resource_string_len(i)) + stats.resources[i];
    buf_size += (stats.players * 7) + stats.players;
    buf_size += (stats.eggs * 4) + stats.eggs;
    printf("Buf size: %zu\n", buf_size + 1);
    return buf_size + 1;
}


static size_t vertical_look(player_t *player, map_t *map,
    vector2l_t *look_vector, map_cell_stats_t *cell_stats)
{
    vector2l_t look_position = VECTOR2L_FROM_U(player->position);
    vector2u_t real_look_position;
    size_t wing_size = 1;
    map_cell_t *cell = NULL;
    size_t cells_visited = 1;
    size_t buf_size = 0;

    for (size_t i = 1; i < player->level; i++) {
        wing_size += 2;
        look_position.y += look_vector->y;
        look_position.x -= (((int)wing_size - 1) / 2) * look_vector->x;
        for (size_t j = 0; j < wing_size; j++) {
            real_look_position = map_resolve_position(map, look_position);
            cell = MAP_CELL_AT_POS(map, real_look_position);
            map_cell_get_stats(cell, &cell_stats[cells_visited]);
            buf_size += cell_stats_buf_size(cell_stats[cells_visited]);
            cells_visited++;
            look_position.x += look_vector->x;
        }
        look_position.x = (long)player->position.x;
    }
    return buf_size;
}

static size_t horizontal_look(player_t *player, map_t *map,
    vector2l_t *look_vector, map_cell_stats_t *cell_stats)
{
    vector2l_t look_position = VECTOR2L_FROM_U(player->position);
    vector2u_t real_look_position;
    size_t wing_size = 1;
    map_cell_t *cell = NULL;
    size_t cells_visited = 1;
    size_t buf_size = 0;

    for (size_t i = 1; i < player->level; i++) {
        wing_size += 2;
        look_position.x += look_vector->x;
        look_position.y -= (((int)wing_size - 1) / 2) * look_vector->y;
        for (size_t j = 0; j < wing_size; j++) {
            real_look_position = map_resolve_position(map, look_position);
            cell = MAP_CELL_AT_POS(map, real_look_position);
            map_cell_get_stats(cell, &cell_stats[cells_visited]);
            buf_size += cell_stats_buf_size(cell_stats[cells_visited]);
            cells_visited++;
            look_position.y += look_vector->y;
        }
        look_position.y = (long)player->position.y;
    }
    return buf_size;
}

static void display_stats(map_cell_stats_t *cell_stats, size_t nb_cells)
{
    for (size_t i = 0; i < nb_cells; i++) {
        printf("Resources: ");
        for (size_t j = 0; j < RES_LEN; j++)
            printf("%zu ", cell_stats[i].resources[j]);
        printf("| Players: ");
        printf("%zu ", cell_stats[i].players);
        printf("| Eggs: ");
        printf("%zu\n", cell_stats[i].eggs);
    }
}

char *player_look(player_t *player, map_t *map)
{
    vector2l_t look_vector = { 0 };
    size_t nb_cells = player->level * player->level;
    map_cell_stats_t *cell_stats = malloc(sizeof(map_cell_stats_t) * nb_cells);
    size_t buffer_size = 3;

    if (cell_stats == NULL)
        return NULL;
    map_cell_get_stats(MAP_PLAYER_CELL(map, player), &cell_stats[0]);
    buffer_size += cell_stats_buf_size(cell_stats[0]);
    get_look_vector(&look_vector, player->direction);
    if (player->direction == DIR_NORTH || player->direction == DIR_SOUTH)
        buffer_size += vertical_look(player, map, &look_vector, cell_stats);
    else
        buffer_size += horizontal_look(player, map, &look_vector, cell_stats);
    printf("Buffer size: %zu\n", buffer_size);
    display_stats(cell_stats, nb_cells);
    free(cell_stats);
    return NULL;
}
