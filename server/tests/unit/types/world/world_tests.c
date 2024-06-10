/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/world/world.h"

Test(world_new_tests, simple_new)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);

    cr_assert_eq(world->map->size.x, 10);
    cr_assert_eq(world->map->size.y, 10);
    cr_assert_eq(world->players->len, 0);
    cr_assert_eq(world->teams->len, 0);
    cr_assert_eq(world->incantations->len, 0);
    cr_assert_eq(world->next_event_delay, 0.0f);
    world_free(world);
}

Test(world_new_tests, world_structure_alloc_fail)
{
    vector2u_t size = { 10, 10 };

    clcc_return_now(calloc, NULL);
    cr_assert_null(world_new(size, 100));
    clcc_disable_control(calloc);
}

Test(world_new_tests, map_structure_alloc_fail)
{
    vector2u_t size = { 10, 10 };

    clcc_return_value_after(calloc, NULL, 1);
    clcc_enable_control(calloc);
    cr_assert_null(world_new(size, 100));
    clcc_disable_control(calloc);
}

Test(world_new_tests, map_cell_structure_alloc_fail)
{
    vector2u_t size = { 10, 10 };

    clcc_return_value_after(calloc, NULL, 2);
    clcc_enable_control(calloc);
    cr_assert_null(world_new(size, 100));
    clcc_disable_control(calloc);
}

Test(world_new_tests, map_cell_row_alloc_fail)
{
    vector2u_t size = { 10, 10 };

    clcc_return_value_after(calloc, NULL, 3);
    clcc_enable_control(calloc);
    cr_assert_null(world_new(size, 100));
    clcc_disable_control(calloc);
}

Test(world_new_tests, map_single_cell_lists_alloc_fail)
{
    vector2u_t size = { 10, 10 };

    clcc_return_now(malloc, NULL);
    clcc_enable_control(malloc);
    cr_assert_null(world_new(size, 100));
    clcc_disable_control(malloc);
}

Test(world_free_tests, free_null_world)
{
    world_free(NULL);
}
