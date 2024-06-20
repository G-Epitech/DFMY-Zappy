/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** string.c
*/

#include <string.h>
#include "types/trantor/resource.h"

static char *resource_str[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

size_t resource_string_len(resource_t resource)
{
    return strlen(resource_str[resource]);
}

char *resource_to_string_ptr(resource_t resource)
{
    return resource_str[resource];
}

void resource_to_string(resource_t resource, char **str)
{
    (*str) = strdup(resource_str[resource]);
}

bool resource_from_string(resource_t *resource, const char *str)
{
    for (resource_t i = RES_FOOD; i < RES_LEN; i++) {
        if (strcmp(str, resource_str[i]) == 0) {
            (*resource) = i;
            return true;
        }
    }
    return false;
}
