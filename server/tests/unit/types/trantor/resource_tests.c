/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/trantor/resource.h"

Test(resources_manager_new_tests, simple_new_with_map_1)
{
    vector2u_t map_size = { 1, 1 };
    resources_manager_t resources_manager;
    size_t resources_limit[RES_LEN] = {
        [RES_FOOD] = 1,
        [RES_LINEMATE] = 1,
        [RES_DERAUMERE] = 1,
        [RES_SIBUR] = 1,
        [RES_MENDIANE] = 1,
        [RES_PHIRAS] = 1,
        [RES_THYSTAME] = 1
    };

    resources_manager_init(&resources_manager, map_size);
    for (resource_t i = 0; i < RES_LEN; i++) {
        cr_expect_eq(resources_manager.stats[i].actual, 0);
        cr_expect_eq(resources_manager.stats[i].limit, resources_limit[i]);
    }
    cr_assert_eq(resources_manager.next_generation,
    RES_MANAGER_NEXT_GENERATION_DELAY);
}

Test(resources_manager_new_tests, simple_new_with_map_10)
{
    vector2u_t map_size = { 10, 10 };
    resources_manager_t resources_manager;
    size_t resources_limit[RES_LEN] = {
        [RES_FOOD] = 50,
        [RES_LINEMATE] = 30,
        [RES_DERAUMERE] = 15,
        [RES_SIBUR] = 10,
        [RES_MENDIANE] = 10,
        [RES_PHIRAS] = 8,
        [RES_THYSTAME] = 5
    };

    resources_manager_init(&resources_manager, map_size);
    for (resource_t i = 0; i < RES_LEN; i++) {
        cr_expect_eq(resources_manager.stats[i].actual, 0);
        cr_expect_eq(resources_manager.stats[i].limit, resources_limit[i],
        "stats[%d].limit = (%lu) should be %lu", i, resources_manager.stats[i].limit, resources_limit[i]);
    }
    cr_assert_eq(resources_manager.next_generation,
    RES_MANAGER_NEXT_GENERATION_DELAY);
}

Test(resources_string_conversion, conversion_tests)
{
    char *str = NULL;
    resource_t resource = RES_FOOD;

    str = strdup("food");
    resource_from_string(&resource, str);
    cr_assert_eq(resource, RES_FOOD);
    free(str);
    str = strdup("unknown");
    cr_assert_eq(resource_from_string(&resource, str), false);
    free(str);
}
