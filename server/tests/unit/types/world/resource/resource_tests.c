/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/world/resource.h"

Test(resource_manager_new_tests, simple_new)
{
    resource_manager_t *resource_manager = resource_manager_new();

    cr_assert_eq(resource_manager->stats[0].limit, 0);
    cr_assert_eq(resource_manager->stats[0].actual, 0);
    cr_assert_eq(resource_manager->next_generation, 0);
    resource_manager_free(resource_manager);
}

Test(resource_manager_new_tests, new_with_calloc_fail)
{
    clcc_return_now(calloc, NULL);
    cr_assert_null(resource_manager_new());
    clcc_disable_control(calloc);
}
