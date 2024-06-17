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

Test(map_move_player_tests, simple_forward)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);
    vector2u_t position = { 4, 4 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    world_add_player(world, player);
    map_player_forward(world->map, player);
    cr_assert_eq(player->position.x, 4);
    cr_assert_eq(player->position.y, 5);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    map_player_forward(world->map, player);
    cr_assert_eq(player->position.x, 5);
    cr_assert_eq(player->position.y, 5);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    map_player_forward(world->map, player);
    cr_assert_eq(player->position.x, 5);
    cr_assert_eq(player->position.y, 4);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    map_player_forward(world->map, player);
    cr_assert_eq(player->position.x, 4);
    cr_assert_eq(player->position.y, 4);
    world_free(world);
    team_free(team);
}

Test(map_move_player_tests, simple_forward_with_unfound_player)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);
    vector2u_t position = { 4, 4 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    map_player_forward(world->map, player);
    cr_assert_eq(player->position.x, 4);
    cr_assert_eq(player->position.y, 4);
    world_free(world);
}

Test(map_move_player_tests, simple_forward_with_null_player)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);

    map_player_forward(world->map, NULL);
    world_free(world);
}

Test(map_move_player_tests, simple_forward_with_null_world)
{
    vector2u_t position = { 4, 4 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    map_player_forward(NULL, player);
    team_free(team);
}

Test(map_take_object_tests, take_object)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);
    vector2u_t position = { 4, 4 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    world_add_player(world, player);
    map_cell_add_resource(&world->map->cells[4][4], RES_FOOD, 1);
    cr_assert_eq(map_player_take_object(world->map, player, RES_FOOD), true);
    cr_assert_eq(world->map->cells[4][4].resources[RES_FOOD], 0);
    cr_assert_eq(player->inventory[RES_FOOD], 1);
    cr_assert_eq(map_player_take_object(world->map, player, RES_LINEMATE), false);
    cr_assert_eq(world->map->cells[4][4].resources[RES_FOOD], 0);
    cr_assert_eq(player->inventory[RES_LINEMATE], 0);
}

Test(map_take_object_tests, take_object_with_null_map)
{
    vector2u_t position = { 4, 4 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    cr_assert_eq(map_player_take_object(NULL, player, RES_FOOD), false);
    team_free(team);
}

Test(map_take_object_tests, take_object_with_null_player)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);

    cr_assert_eq(map_player_take_object(world->map, NULL, RES_FOOD), false);
    world_free(world);
}

Test(map_set_object_tests, set_object)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);
    vector2u_t position = { 4, 4 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    world_add_player(world, player);
    player->inventory[RES_FOOD] = 1;
    cr_assert_eq(map_player_set_object(world->map, player, RES_FOOD), true);
    cr_assert_eq(world->map->cells[4][4].resources[RES_FOOD], 1);
    cr_assert_eq(player->inventory[RES_FOOD], 0);
    cr_assert_eq(map_player_set_object(world->map, player, RES_LINEMATE), false);
    cr_assert_eq(world->map->cells[4][4].resources[RES_LINEMATE], 0);
    cr_assert_eq(player->inventory[RES_LINEMATE], 0);
}

Test(map_set_object_tests, set_object_with_null_map)
{
    vector2u_t position = { 4, 4 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    cr_assert_eq(map_player_set_object(NULL, player, RES_FOOD), false);
    team_free(team);
}

Test(map_set_object_tests, set_object_with_null_player)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);

    cr_assert_eq(map_player_set_object(world->map, NULL, RES_FOOD), false);
    world_free(world);
}

Test(map_add_resource_tests, add_resource_to_null_cell)
{
    map_cell_add_resource(NULL, RES_FOOD, 1);
}

Test(map_remove_resource_tests, remove_resource_from_null_cell)
{
    map_cell_remove_resource(NULL, RES_FOOD, 1);
}

Test(map_remove_resource_tests, remove_resource_from_cell)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);

    map_cell_add_resource(&world->map->cells[4][4], RES_FOOD, 1);
    map_cell_remove_resource(&world->map->cells[4][4], RES_FOOD, 1);
    cr_assert_eq(world->map->cells[4][4].resources[RES_FOOD], 0);
    world_free(world);
}
