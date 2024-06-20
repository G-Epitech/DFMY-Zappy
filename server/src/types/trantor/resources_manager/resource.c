/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** string.c
*/

#include <string.h>
#include "types/trantor/resource.h"

const char *resource_str[] = {
        "food",
        "linemate",
        "deraumere",
        "sibur",
        "mendiane",
        "phiras",
        "thystame",
        NULL
};

void resource_to_str(resource_t resource, char **str)
{
    (*str) = strdup(resource_str[resource]);
}

bool resource_from_str(resource_t *resource, const char *str)
{
    for (resource_t i = RES_FOOD; i < RES_LEN; i++) {
        if (strcmp(str, resource_str[i]) == 0) {
            *resource = i;
            return true;
        }
    }
    return false;
}

