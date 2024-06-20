/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** string.c
*/

#include <memory.h>
#include <stdio.h>
#include "types/trantor/resource.h"
#include "types/trantor/map.h"

static void look_string_cell(char *buffer, map_cell_stats_t *cell_stats,
    size_t *buf_idx)
{
    char *resource_str = NULL;

    for (resource_t j = RES_FOOD; j < RES_LEN; j++) {
        for (size_t k = 0; k < cell_stats->resources[j]; k++) {
            resource_str = resource_to_str_ptr(j);
            memcpy(&buffer[(*buf_idx)], resource_str, strlen(resource_str));
            (*buf_idx) += strlen(resource_str);
            buffer[(*buf_idx)] = ' ';
            *buf_idx += 1;
        }
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

char *player_look_string(map_cell_stats_t *cell_stats, size_t nb_cells,
    size_t buf_size)
{
    char *buffer = malloc(sizeof(char) * buf_size);
    size_t buf_idx = 1;

    if (buffer == NULL)
        return NULL;
    buffer[0] = '[';
    for (size_t i = 0; i < nb_cells; i++) {
        look_string_cell(buffer, &cell_stats[i], &buf_idx);
    }
    buffer[buf_idx] = ']';
    printf("%zu\n", buf_idx + 1);
    buffer[buf_idx + 1] = '\0';
    return buffer;
}
