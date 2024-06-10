/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Resource manager new
*/

#include <stdlib.h>
#include <memory.h>
#include "types/world/resource.h"

static void resource_manager_init_stats(resource_manager_t *manager)
{
    for (int i = 0; i < RES_LEN; i++) {
        manager->stats[i].actual = 0;
        manager->stats[i].limit = 0;
    }
}

resource_manager_t *resource_manager_new(void)
{
    resource_manager_t *manager = calloc(1, sizeof(resource_manager_t));

    if (!manager)
        return NULL;
    manager->next_generation = 0;
    resource_manager_init_stats(manager);
    return manager;
}
