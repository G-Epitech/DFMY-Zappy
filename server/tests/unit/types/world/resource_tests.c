/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/world/resource.h"

Test(resources_manager_new_tests, simple_new)
{
    vector2u_t map_size = { 1, 1 };
    resources_manager_t resources_manager;

    resources_manager_init(&resources_manager, map_size);
    cr_assert_eq(resources_manager.stats[RES_FOOD].limit, 1);
    cr_assert_eq(resources_manager.stats[RES_FOOD].actual, 0);
    cr_assert_eq(resources_manager.stats[RES_LINEMATE].limit, 1);
    cr_assert_eq(resources_manager.stats[RES_LINEMATE].actual, 0);
    cr_assert_eq(resources_manager.stats[RES_DERAUMERE].limit, 1);
    cr_assert_eq(resources_manager.stats[RES_DERAUMERE].actual, 0);
    cr_assert_eq(resources_manager.stats[RES_SIBUR].limit, 1);
    cr_assert_eq(resources_manager.stats[RES_SIBUR].actual, 0);
    cr_assert_eq(resources_manager.stats[RES_MENDIANE].limit, 1);
    cr_assert_eq(resources_manager.stats[RES_MENDIANE].actual, 0);
    cr_assert_eq(resources_manager.stats[RES_PHIRAS].limit, 1);
    cr_assert_eq(resources_manager.stats[RES_PHIRAS].actual, 0);
    cr_assert_eq(resources_manager.stats[RES_THYSTAME].limit, 1);
    cr_assert_eq(resources_manager.stats[RES_THYSTAME].actual, 0);
    cr_assert_eq(resources_manager.next_generation,
    RES_MANAGER_NEXT_GENERATION_DELAY);
}
