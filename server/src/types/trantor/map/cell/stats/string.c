/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** string.c
*/

#include <memory.h>
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
    buf_size += (stats->players * 7);
    buf_size += (stats->eggs * 4);
    return buf_size + 1;
}

static void map_cell_stats_resources_string(map_cell_stats_t *cell_stats,
    resource_t resource, size_t *buf_idx, char *buffer)
{
    char *resource_str = NULL;

    for (size_t k = 0; k < cell_stats->resources[resource]; k++) {
        resource_str = resource_to_string_ptr(resource);
        memcpy(&buffer[(*buf_idx)], resource_str, strlen(resource_str));
        (*buf_idx) += strlen(resource_str);
        buffer[(*buf_idx)] = ' ';
        *buf_idx += 1;
    }
}

static void map_cell_stats_string(char *buffer, map_cell_stats_t *cell_stats,
    size_t *buf_idx)
{
    for (resource_t j = RES_FOOD; j < RES_LEN; j++) {
        map_cell_stats_resources_string(cell_stats, j, buf_idx, buffer);
    }
    for (size_t j = 0; j < cell_stats->players; j++) {
        memcpy(&buffer[(*buf_idx)], "player ", 7);
        *buf_idx += 7;
    }
    for (size_t j = 0; j < cell_stats->eggs; j++) {
        memcpy(&buffer[(*buf_idx)], "egg ", 4);
        (*buf_idx) += 4;
    }
    buffer[(*buf_idx)] = ',';
    (*buf_idx) += 1;
}

char *map_cells_stats_string(map_cell_stats_t *cell_stats, size_t nb_cells,
    size_t buf_size)
{
    char *buffer = malloc(sizeof(char) * buf_size + 3);
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
