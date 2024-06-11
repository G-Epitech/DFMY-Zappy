/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include "clcc/modules/stdlib.h"
#include "types/world/world.h"

Test(map_tests, simple_init_cell)
{
    map_cell_t cell = { 0 };

    cr_assert_eq(map_cell_init(&cell), true);
    cr_assert_eq(cell.resources[RES_FOOD], 0);
    cr_assert_eq(cell.resources[RES_LINEMATE], 0);
    cr_assert_eq(cell.resources[RES_DERAUMERE], 0);
    cr_assert_eq(cell.resources[RES_SIBUR], 0);
    cr_assert_eq(cell.resources[RES_MENDIANE], 0);
    cr_assert_eq(cell.resources[RES_PHIRAS], 0);
    cr_assert_eq(cell.resources[RES_THYSTAME], 0);
    cr_assert_not_null(cell.players);
    cr_assert_not_null(cell.eggs);
    map_cell_free(&cell);
}

Test(map_tests, init_cell_fail_due_to_eggs_list_alloc_fail)
{
    map_cell_t cell = { 0 };

    clcc_return_now(malloc, NULL);
    cr_assert_eq(map_cell_init(&cell), false);
    clcc_disable_control(malloc);
}

Test(map_tests, init_cell_fail_due_to_players_list_alloc_fail)
{
    map_cell_t cell = { 0 };

    clcc_return_value_after(malloc, NULL, 1);
    clcc_enable_control(malloc);
    cr_assert_eq(map_cell_init(&cell), false);
    clcc_disable_control(malloc);
}

Test(map_tests, simple_new)
{
    vector2u_t size = { 10, 10 };
    map_t *map = map_new(size);

    cr_assert_eq(map->size.x, 10);
    cr_assert_eq(map->size.y, 10);
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            cr_assert_not_null(map->cells[i][j].players);
            cr_assert_not_null(map->cells[i][j].eggs);
        }
    }
    map_free(map);
}

Test(map_tests, map_alloc_fail)
{
    vector2u_t size = { 10, 10 };

    clcc_return_now(calloc, NULL);
    cr_assert_null(map_new(size));
    clcc_disable_control(calloc);
}
