/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Resource manager free
*/

#include <stdlib.h>
#include "types/resource.h"

void resource_manager_free(resource_manager_t *manager)
{
    if (manager)
        free(manager);
}
