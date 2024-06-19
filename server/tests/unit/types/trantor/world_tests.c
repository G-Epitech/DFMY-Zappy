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
#include "types/trantor/incantation.h"

Test(world_new_tests, simple_new)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    size_t resources_limit[RES_LEN] = {
        [RES_FOOD] = 50,
        [RES_LINEMATE] = 30,
        [RES_DERAUMERE] = 15,
        [RES_SIBUR] = 10,
        [RES_MENDIANE] = 10,
        [RES_PHIRAS] = 8,
        [RES_THYSTAME] = 5
    };

    cr_assert_eq(world->map->size.x, 10);
    cr_assert_eq(world->map->size.y, 10);
    cr_assert_eq(world->players->len, 0);
    cr_assert_eq(world->teams->len, 0);
    cr_assert_eq(world->incantations->len, 0);
    cr_assert_eq(world->next_event_delay, -1.0f);
    for (resource_t i = 0; i < RES_LEN; i++) {
        cr_expect_eq(world->resources_manager.stats[i].actual, 0);
        cr_expect_eq(world->resources_manager.stats[i].limit, resources_limit[i]);
    }
    world_free(world);
}

Test(world_new_tests, world_structure_alloc_fail)
{
    vector2u_t size = { 10, 10 };

    clcc_return_now(calloc, NULL);
    cr_assert_null(world_new(size, 100));
    clcc_disable_control(calloc);
}

Test(world_new_tests, teams_alloc_fail)
{
    vector2u_t size = { 10, 10 };

    clcc_return_value_after(malloc, NULL, 200);
    clcc_enable_control(malloc);
    cr_assert_null(world_new(size, 100));
    clcc_disable_control(malloc);
}

Test(world_new_tests, players_alloc_fail)
{
    vector2u_t size = { 10, 10 };

    clcc_return_value_after(malloc, NULL, 201);
    clcc_enable_control(malloc);
    cr_assert_null(world_new(size, 100));
    clcc_disable_control(malloc);
}

Test(world_new_tests, incantations_alloc_fail)
{
    vector2u_t size = { 10, 10 };

    clcc_return_value_after(malloc, NULL, 202);
    clcc_enable_control(malloc);
    cr_assert_null(world_new(size, 100));
    clcc_disable_control(malloc);
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

Test(world_free_tests, free_null_map_cell)
{
    map_cell_free(NULL);
}

Test(world_register_event, simple)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);

    world_register_event(world, 10);
    cr_assert_eq(world->next_event_delay, 10);
    world_register_event(world, 5);
    cr_assert_eq(world->next_event_delay, 5);
    world_register_event(world, 6);
    cr_assert_eq(world->next_event_delay, 5);
    world_reset_event_delay(world);
    cr_assert_eq(world->next_event_delay, -1);
    world_free(world);
}

Test(world_add_player_tests, add_player_to_world)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    vector2u_t position = { 5, 5 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    cr_assert_eq(world_add_player(world, player), true);
    cr_assert_eq(world->players->len, 1);
    cr_assert_eq(world->players->first->data.ptr, player);
    world_free(world);
    team_free(team);
}

Test(world_add_player_tests, add_player_to_world_fail_push_world)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    vector2u_t position = { 5, 5 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    clcc_return_now(malloc, NULL);
    cr_assert_eq(world_add_player(world, player), false);
    clcc_disable_control(malloc);
    cr_assert_eq(world->players->len, 0);
    world_free(world);
    team_free(team);
}

Test(world_add_player_tests, add_player_to_world_fail_push_world_cell)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    vector2u_t position = { 5, 5 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    clcc_return_value_after(malloc, NULL, 1);
    clcc_enable_control(malloc);
    cr_assert_eq(world_add_player(world, player), false);
    clcc_disable_control(malloc);
    world_free(world);
    team_free(team);
}

Test(world_add_player_tests, add_player_to_world_fail_push_world_team)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    vector2u_t position = { 5, 5 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    clcc_return_value_after(malloc, NULL, 2);
    clcc_enable_control(malloc);
    cr_assert_eq(world_add_player(world, player), false);
    clcc_disable_control(malloc);
    world_free(world);
    team_free(team);
}

Test(world_remove_player_tests, remove_player_from_everything)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    vector2u_t position = { 5, 5 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);
    incantation_t *incantation = incantation_new(1);

    world_add_player(world, player);
    list_push(world->incantations, NODE_DATA_FROM_PTR(incantation));
    incantation_add_player(incantation, player);
    cr_assert_eq(world->players->len, 1);
    cr_assert_eq(world->incantations->len, 1);
    world_remove_player(world, player);
    cr_assert_eq(world->players->len, 0);
    cr_assert_eq(incantation->players->len, 0);
}

Test(world_remove_player_tests, remove_unadded_player_from_everything)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    vector2u_t position = { 5, 5 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);
    player_t *player2 = player_new(NULL, team, position);
    incantation_t *incantation = incantation_new(1);

    world_add_player(world, player2);
    incantation_add_player(incantation, player2);
    list_push(world->incantations, NODE_DATA_FROM_PTR(incantation));
    cr_assert_eq(world->next_player_id, 1);
    cr_assert_eq(player->id, 0);
    cr_assert_eq(world->players->len, 1);
    cr_assert_eq(world->incantations->len, 1);
    world_remove_player(world, player);
    cr_assert_eq(world->players->len, 1);
    cr_assert_eq(incantation->players->len, 1);
}

Test(incantation_tests, sucesful_incantation)
{
    vector2u_t size = { 10, 10 };
    vector2u_t pos = { 1, 1 };
    world_t *world = world_new(size, 2);
    player_t *player = player_new(NULL, NULL, pos);
    player_t *player2 = player_new(NULL, NULL, pos);
    map_cell_t *cell = NULL;
    incantation_t *incantation = NULL;

    cr_assert_not_null(world);
    cell = MAP_CELL_AT_POS(world->map, pos);
    list_push(cell->players, NODE_DATA_FROM_PTR(player));
    list_push(cell->players, NODE_DATA_FROM_PTR(player2));
    cr_assert_not_null(cell);
    cr_assert_eq(cell->players->len, 2);
    cell->resources[RES_LINEMATE] = 1;
    incantation = world_start_incantation(world, player);
    cr_assert_not_null(incantation);
    cr_assert_eq(incantation->players->len, 2);
    cr_assert_eq(world_end_incantation(world, incantation), true);
    cr_assert_eq(player->level, 2);
    cr_assert_eq(player2->level, 2);
    cr_assert_eq(cell->resources[RES_LINEMATE], 0);
    cr_assert_eq(world->incantations->len, 0);
    cr_assert_null(player->incantation);
    world_free(world);
    player_free(player2);
    player_free(player);
}

Test(incantation_tests, failed_end)
{
    vector2u_t size = { 10, 10 };
    vector2u_t pos = { 1, 1 };
    world_t *world = world_new(size, 2);
    player_t *player = player_new(NULL, NULL, pos);
    map_cell_t *cell = NULL;
    incantation_t *incantation = NULL;

    cr_assert_not_null(world);
    cell = MAP_CELL_AT_POS(world->map, pos);
    list_push(cell->players, NODE_DATA_FROM_PTR(player));
    cr_assert_not_null(cell);
    cr_assert_eq(cell->players->len, 1);
    cell->resources[RES_LINEMATE] = 1;
    incantation = world_start_incantation(world, player);
    cr_assert_not_null(incantation);
    cr_assert_eq(incantation->players->len, 1);
    cell->resources[RES_LINEMATE] = 0;
    cr_assert_eq(world_end_incantation(world, incantation), false);
    cr_assert_eq(player->level, 1);
    cr_assert_eq(cell->resources[RES_LINEMATE], 0);
    cr_assert_eq(world->incantations->len, 0);
    cr_assert_null(player->incantation);
    world_free(world);
    player_free(player);
}

Test(incantation_tests, calloc_fail)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 2);
    player_t *player = player_new(NULL, NULL, (vector2u_t) { 1, 1 });

    cr_assert_not_null(world);
    clcc_return_now(calloc, NULL);
    cr_assert_null(world_start_incantation(world, player));
    clcc_disable_control(calloc);
    world_free(world);
    player_free(player);
}

Test(incantation_tests, incantation_invalid_level)
{
    vector2u_t size = { 10, 10 };
    vector2u_t pos = { 1, 1 };
    world_t *world = world_new(size, 2);
    player_t *player = player_new(NULL, NULL, pos);
    map_cell_t *cell = NULL;
    incantation_t *incantation = NULL;

    cr_assert_not_null(world);
    cell = MAP_CELL_AT_POS(world->map, pos);
    list_push(cell->players, NODE_DATA_FROM_PTR(player));
    cr_assert_not_null(cell);
    cr_assert_eq(cell->players->len, 1);
    cell->resources[RES_LINEMATE] = 1;
    player->level = 8;
    incantation = world_start_incantation(world, player);
    cr_assert_null(incantation);
    world_free(world);
    player_free(player);
}

Test(incantation_tests, not_enough_players)
{
    vector2u_t size = { 10, 10 };
    vector2u_t pos = { 1, 1 };
    world_t *world = world_new(size, 2);
    player_t *player = player_new(NULL, NULL, pos);
    map_cell_t *cell = NULL;
    incantation_t *incantation = NULL;

    cr_assert_not_null(world);
    cell = MAP_CELL_AT_POS(world->map, pos);
    list_push(cell->players, NODE_DATA_FROM_PTR(player));
    cr_assert_not_null(cell);
    cr_assert_eq(cell->players->len, 1);
    player->level = 2;
    cell->resources[RES_LINEMATE] = 1;
    cell->resources[RES_DERAUMERE] = 1;
    cell->resources[RES_SIBUR] = 1;
    incantation = world_start_incantation(world, player);
    cr_assert_null(incantation);
    world_free(world);
    player_free(player);
}

Test(incantation_tests, not_enough_players_with_correct_levels)
{
    vector2u_t size = { 10, 10 };
    vector2u_t pos = { 1, 1 };
    world_t *world = world_new(size, 2);
    player_t *player = player_new(NULL, NULL, pos);
    player_t *player2 = player_new(NULL, NULL, pos);
    map_cell_t *cell = NULL;
    incantation_t *incantation = NULL;

    cr_assert_not_null(world);
    cell = MAP_CELL_AT_POS(world->map, pos);
    list_push(cell->players, NODE_DATA_FROM_PTR(player));
    list_push(cell->players, NODE_DATA_FROM_PTR(player2));
    cr_assert_not_null(cell);
    cr_assert_eq(cell->players->len, 2);
    player->level = 2;
    player2->level = 1;
    cell->resources[RES_LINEMATE] = 1;
    cell->resources[RES_DERAUMERE] = 1;
    cell->resources[RES_SIBUR] = 1;
    incantation = world_start_incantation(world, player);
    cr_assert_null(incantation);
    world_free(world);
    player_free(player2);
    player_free(player);
}

Test(incantation_tests, incantation_level_two)
{
    vector2u_t size = { 10, 10 };
    vector2u_t pos = { 1, 1 };
    world_t *world = world_new(size, 2);
    player_t *player = player_new(NULL, NULL, pos);
    player_t *player2 = player_new(NULL, NULL, pos);
    player_t *player3 = player_new(NULL, NULL, pos);
    map_cell_t *cell = NULL;
    incantation_t *incantation = NULL;

    cr_assert_not_null(world);
    cell = MAP_CELL_AT_POS(world->map, pos);
    list_push(cell->players, NODE_DATA_FROM_PTR(player));
    list_push(cell->players, NODE_DATA_FROM_PTR(player2));
    list_push(cell->players, NODE_DATA_FROM_PTR(player3));
    cr_assert_not_null(cell);
    cr_assert_eq(cell->players->len, 3);
    player->level = 2;
    player2->level = 2;
    player3->level = 1;
    cell->resources[RES_LINEMATE] = 1;
    cell->resources[RES_DERAUMERE] = 1;
    cell->resources[RES_SIBUR] = 1;
    incantation = world_start_incantation(world, player);
    cr_assert_not_null(incantation);
    cr_assert_eq(incantation->players->len, 2);
    cr_assert_eq(world_end_incantation(world, incantation), true);
    cr_assert_eq(player->level, 3);
    cr_assert_eq(player2->level, 3);
    cr_assert_eq(player3->level, 1);
    cr_assert_eq(cell->resources[RES_LINEMATE], 0);
    cr_assert_eq(cell->resources[RES_DERAUMERE], 0);
    cr_assert_eq(cell->resources[RES_SIBUR], 0);
    cr_assert_eq(world->incantations->len, 0);
    cr_assert_null(player->incantation);
    world_free(world);
    player_free(player3);
    player_free(player2);
    player_free(player);
}
