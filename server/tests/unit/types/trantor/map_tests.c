/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include "clcc/modules/stdlib.h"
#include "types/trantor/world.h"

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

Test(map_add_resource_tests, add_resource_to_null_cell)
{
    vector2u_t position = { 4, 4 };

    map_add_resource(NULL, position, RES_FOOD, 1);
}

Test(map_remove_resource_tests, remove_resource_from_null_cell)
{
    vector2u_t position = { 4, 4 };

    map_remove_resource(NULL, position, RES_FOOD, 1);
}

Test(map_remove_resource_tests, remove_resource_from_cell)
{
    vector2u_t size = { 6, 6 };
    vector2u_t position = { 4, 4 };
    world_t *world = world_new(size, 100);

    map_add_resource(world->map, position, RES_FOOD, 1);
    map_remove_resource(world->map, position, RES_FOOD, 1);
    cr_assert_eq(world->map->cells[4][4].resources[RES_FOOD], 0);
    world_free(world);
}

Test(map_remove_resource_tests, remove_resource_empty_cell)
{
    vector2u_t size = { 6, 6 };
    vector2u_t position = { 4, 4 };
    world_t *world = world_new(size, 100);

    map_remove_resource(world->map, position, RES_FOOD, 1);
    cr_assert_eq(world->map->cells[4][4].resources[RES_FOOD], 0);
    world_free(world);
}

Test(map_resolve_position, resolve_position)
{
    vector2l_t pos = {-1, 0 };
    vector2u_t map_size = { 10, 10 };
    map_t *map = map_new(map_size);
    vector2u_t resolved_pos = map_resolve_position(map, pos);

    cr_assert_eq(resolved_pos.x, 9);
    cr_assert_eq(resolved_pos.y, 0);
    pos = (vector2l_t){10, 0 };
    resolved_pos = map_resolve_position(map, pos);
    cr_assert_eq(resolved_pos.x, 0);
    cr_assert_eq(resolved_pos.y, 0);
    pos = (vector2l_t){11, 0 };
    resolved_pos = map_resolve_position(map, pos);
    cr_assert_eq(resolved_pos.x, 1);
    cr_assert_eq(resolved_pos.y, 0);
    pos = (vector2l_t){-51, 0 };
    resolved_pos = map_resolve_position(map, pos);
    cr_assert_eq(resolved_pos.x, 9);
    cr_assert_eq(resolved_pos.y, 0);
    pos = (vector2l_t){4, 4 };
    resolved_pos = map_resolve_position(map, pos);
    cr_assert_eq(resolved_pos.x, 4);
    cr_assert_eq(resolved_pos.y, 4);
    pos = (vector2l_t){1, -1 };
    resolved_pos = map_resolve_position(map, pos);
    cr_assert_eq(resolved_pos.x, 1);
    cr_assert_eq(resolved_pos.y, 9);
    map_free(map);
}

Test(map_broadcast_angle_tests, subject_example)
{
    vector2u_t size = {11, 11};
    world_t *world = world_new(size, 2);
    vector2u_t dest_pos = {5, 2};
    vector2u_t src_pos = {2, 9};
    double final_angle = (map_get_sound_angle(world->map, src_pos, dest_pos));
    int quadrant  = angle_to_quadrant(final_angle);
    int normalized_quadrant = direction_get_quadrant(DIR_EAST, quadrant);

    cr_assert_eq(normalized_quadrant, 4);
    normalized_quadrant = direction_get_quadrant(DIR_SOUTH, quadrant);
    cr_assert_eq(normalized_quadrant, 6);
    normalized_quadrant = direction_get_quadrant(DIR_NORTH, quadrant);
    cr_assert_eq(normalized_quadrant, 2);
    normalized_quadrant = direction_get_quadrant(DIR_WEST, quadrant);
    cr_assert_eq(normalized_quadrant, 8);
    free(world);
}

Test(map_broadcast_angle_tests, reversed_x_subject_example)
{
    vector2u_t size = {11, 11};
    world_t *world = world_new(size, 2);
    vector2u_t dest_pos = {2, 2};
    vector2u_t src_pos = {5, 9};
    double final_angle = (map_get_sound_angle(world->map, src_pos, dest_pos));
    int quadrant  = angle_to_quadrant(final_angle);
    int normalized_quadrant = direction_get_quadrant(DIR_EAST, quadrant);

    cr_assert_eq(normalized_quadrant, 2);
    normalized_quadrant = direction_get_quadrant(DIR_SOUTH, quadrant);
    cr_assert_eq(normalized_quadrant, 4);
    normalized_quadrant = direction_get_quadrant(DIR_NORTH, quadrant);
    cr_assert_eq(normalized_quadrant, 8);
    normalized_quadrant = direction_get_quadrant(DIR_WEST, quadrant);
    cr_assert_eq(normalized_quadrant, 6);
    free(world);
}

Test(map_broadcast_angle_tests, reversed_y_subject_example)
{
    vector2u_t size = {11, 11};
    world_t *world = world_new(size, 2);
    vector2u_t dest_pos = {5, 9};
    vector2u_t src_pos = {2, 2};
    double final_angle = (map_get_sound_angle(world->map, src_pos, dest_pos));
    int quadrant  = angle_to_quadrant(final_angle);
    int normalized_quadrant = direction_get_quadrant(DIR_EAST, quadrant);

    cr_assert_eq(normalized_quadrant, 6);
    normalized_quadrant = direction_get_quadrant(DIR_SOUTH, quadrant);
    cr_assert_eq(normalized_quadrant, 8);
    normalized_quadrant = direction_get_quadrant(DIR_NORTH, quadrant);
    cr_assert_eq(normalized_quadrant, 4);
    normalized_quadrant = direction_get_quadrant(DIR_WEST, quadrant);
    cr_assert_eq(normalized_quadrant, 2);
    free(world);
}

Test(map_broadcast_angle_tests, reversed_y_x_subject_example)
{
    vector2u_t size = {11, 11};
    world_t *world = world_new(size, 2);
    vector2u_t dest_pos = {2, 9};
    vector2u_t src_pos = {5, 2};
    double final_angle = (map_get_sound_angle(world->map, src_pos, dest_pos));
    int quadrant  = angle_to_quadrant(final_angle);
    int normalized_quadrant = direction_get_quadrant(DIR_EAST, quadrant);

    cr_assert_eq(normalized_quadrant, 8);
    normalized_quadrant = direction_get_quadrant(DIR_SOUTH, quadrant);
    cr_assert_eq(normalized_quadrant, 2);
    normalized_quadrant = direction_get_quadrant(DIR_NORTH, quadrant);
    cr_assert_eq(normalized_quadrant, 6);
    normalized_quadrant = direction_get_quadrant(DIR_WEST, quadrant);
    cr_assert_eq(normalized_quadrant, 4);
    free(world);
}

Test(map_broadcast_angle_tests, same_tile)
{
    vector2u_t size = {11, 11};
    world_t *world = world_new(size, 2);
    vector2u_t dest_pos = {2, 2};
    vector2u_t src_pos = {2, 2};
    double final_angle = (map_get_sound_angle(world->map, src_pos, dest_pos));
    int quadrant  = angle_to_quadrant(final_angle);

    cr_assert_eq(direction_get_quadrant(DIR_EAST, quadrant), 1);
    cr_assert_eq(direction_get_quadrant(DIR_SOUTH, quadrant), 3);
    cr_assert_eq(direction_get_quadrant(DIR_NORTH, quadrant), 7);
    cr_assert_eq(direction_get_quadrant(DIR_WEST, quadrant), 5);
    free(world);
}

Test(map_broadcast_angle_tests, null_map)
{
    vector2u_t dest_pos = {2, 2};
    vector2u_t src_pos = {2, 2};
    double final_angle = (map_get_sound_angle(NULL, src_pos, dest_pos));
    int quadrant  = angle_to_quadrant(final_angle);

    cr_assert_eq(final_angle, -1);
    cr_assert_eq(quadrant, -1);
    cr_assert_eq(direction_get_quadrant(DIR_EAST, quadrant), -1);
    cr_assert_eq(direction_get_quadrant(DIR_SOUTH, quadrant), -1);
    cr_assert_eq(direction_get_quadrant(DIR_NORTH, quadrant), -1);
    cr_assert_eq(direction_get_quadrant(DIR_WEST, quadrant), -1);
}

Test(map_broadcast_angle_tests, wrap_on_x_dest_bigger)
{
    vector2u_t size = {11, 11};
    world_t *world = world_new(size, 2);
    vector2u_t dest_pos = {8, 5};
    vector2u_t src_pos = {1, 5};
    double final_angle = (map_get_sound_angle(world->map, src_pos, dest_pos));
    int quadrant  = angle_to_quadrant(final_angle);
    int normalized_quadrant = direction_get_quadrant(DIR_EAST, quadrant);

    cr_assert_eq(normalized_quadrant, 1);
    normalized_quadrant = direction_get_quadrant(DIR_SOUTH, quadrant);
    cr_assert_eq(normalized_quadrant, 3);
    normalized_quadrant = direction_get_quadrant(DIR_NORTH, quadrant);
    cr_assert_eq(normalized_quadrant, 7);
    normalized_quadrant = direction_get_quadrant(DIR_WEST, quadrant);
    cr_assert_eq(normalized_quadrant, 5);
    free(world);
}

Test(map_broadcast_angle_tests, wrap_on_x_src_bigger)
{
    vector2u_t size = {11, 11};
    world_t *world = world_new(size, 2);
    vector2u_t dest_pos = {1, 5};
    vector2u_t src_pos = {8, 5};
    double final_angle = (map_get_sound_angle(world->map, src_pos, dest_pos));
    int quadrant  = angle_to_quadrant(final_angle);
    int normalized_quadrant = direction_get_quadrant(DIR_EAST, quadrant);

    cr_assert_eq(normalized_quadrant, 5);
    normalized_quadrant = direction_get_quadrant(DIR_SOUTH, quadrant);
    cr_assert_eq(normalized_quadrant, 7);
    normalized_quadrant = direction_get_quadrant(DIR_NORTH, quadrant);
    cr_assert_eq(normalized_quadrant, 3);
    normalized_quadrant = direction_get_quadrant(DIR_WEST, quadrant);
    cr_assert_eq(normalized_quadrant, 1);
    free(world);
}
