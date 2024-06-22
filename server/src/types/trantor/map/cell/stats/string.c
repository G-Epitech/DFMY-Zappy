/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** string.c
*/

#include <memory.h>
#include "utils.h"
#include "types/trantor/resource.h"
#include "types/trantor/map.h"

size_t map_cell_stats_str_len(map_cell_stats_t *stats)
{
    size_t buf_size = 0;

    for (resource_t i = RES_FOOD; i < RES_LEN; i++) {
        if (stats->resources[i] > 0) {
            buf_size += (stats->resources[i] * resource_string_len(i) + 1);
        }
    }
    buf_size += (stats->players * STR_STRICT_SIZEOF("player "));
    buf_size += (stats->eggs * STR_STRICT_SIZEOF("egg "));
    return buf_size + 1;
}

static void map_cell_stats_resources_string(map_cell_stats_t *cell_stats,
    resource_t resource, size_t *buf_idx, char *buffer)
{
    const char *resource_str = NULL;
    size_t resource_len = 0;

    for (size_t k = 0; k < cell_stats->resources[resource]; k++) {
        resource_str = resource_to_string(resource);
        resource_len = strlen(resource_str);
        memcpy(&buffer[(*buf_idx)], resource_str, resource_len);
        (*buf_idx) += resource_len;
        buffer[(*buf_idx)] = ' ';
        (*buf_idx) += 1;
    }
}

static void map_cell_stats_string(char *buffer, map_cell_stats_t *cell_stats,
    size_t *buf_idx)
{
    size_t player_buf_size = STR_STRICT_SIZEOF("player ");
    size_t egg_buf_size = STR_STRICT_SIZEOF("egg ");

    for (resource_t j = RES_FOOD; j < RES_LEN; j++) {
        map_cell_stats_resources_string(cell_stats, j, buf_idx, buffer);
    }
    for (size_t j = 0; j < cell_stats->players; j++) {
        memcpy(&buffer[(*buf_idx)], "player ", player_buf_size);
        (*buf_idx) += player_buf_size;
    }
    for (size_t j = 0; j < cell_stats->eggs; j++) {
        memcpy(&buffer[(*buf_idx)], "egg ", egg_buf_size);
        (*buf_idx) += egg_buf_size;
    }
    buffer[(*buf_idx)] = ',';
    (*buf_idx) += 1;
}

char *map_cells_stats_string(map_cell_stats_t *cell_stats, size_t nb_cells,
    size_t buf_size)
{
    char *buffer = calloc(buf_size + 3, sizeof(char));
    size_t buf_idx = 1;

    if (buffer == NULL)
        return NULL;
    buffer[0] = '[';
    for (size_t i = 0; i < nb_cells; i++) {
        map_cell_stats_string(buffer, &cell_stats[i], &buf_idx);
    }
    buffer[buf_idx] = ']';
    buffer[buf_idx + 1] = '\0';
    return buffer;
}
