/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** incantation_tests.c
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/world/incantation.h"
#include "types/world/player.h"
#include "types/world/world.h"

Test(incantation_tests, new_incantation)
{
    player_controller_t *requester = calloc(1, sizeof(player_controller_t));
    incantation_t *incantation = incantation_new(7);

    cr_assert_not_null(incantation);
    cr_assert_eq(incantation->cooldown, INCANTATION_DURATION);
    cr_assert_eq(incantation->level, 7);
    cr_assert_null(incantation->requester);
    cr_assert_not_null(incantation->players);
    cr_assert_eq(incantation->players->len, 0);
    incantation_free(incantation);
    free(requester);
}

Test(incantation_tests, new_incantation_fail_due_to_calloc)
{
    clcc_return_now(calloc, NULL);
    cr_assert_null(incantation_new(7));
    clcc_disable_control(calloc);
}

Test(incantation_tests, new_incantation_fail_due_to_players_list_new)
{
    clcc_return_now(malloc, NULL);
    cr_assert_null(incantation_new(7));
    clcc_disable_control(malloc);
}

Test(incantation_tests, free_incantation)
{
    incantation_t *incantation = incantation_new(7);

    incantation_free(incantation);
}

Test(incantation_tests, free_null_incantation)
{
    incantation_free(NULL);
}

Test(incantation_tests, free_list_of_incantations)
{
    list_t *incantations = list_new();

    cr_assert_eq(incantations->len, 0);
    for (int i = 0; i < 5; i++) {
        incantation_t *incantation = incantation_new(7);

        cr_assert_not_null(incantation);
        list_push(incantations, NODE_DATA_FROM_PTR(incantation));
        cr_assert_eq(incantations->len, i + 1);
    }
    cr_assert_eq(incantations->len, 5);
    list_clear(incantations, &incantation_free_as_node_data);
    cr_assert_eq(incantations->len, 0);
    list_free(incantations, NULL);
}

Test(incantation_tests, simple_add_player)
{
    player_t *player1 = player_new(NULL, NULL, (vector2u_t) { 1, 1 });
    player_t *player2 = player_new(NULL, NULL, (vector2u_t) { 1, 1 });
    incantation_t *incantation = incantation_new(7);

    cr_assert_eq(incantation->players->len, 0);
    cr_assert_eq(incantation_add_player(incantation, player2), true);
    cr_assert_eq(incantation_add_player(incantation, player1), true);
    cr_assert_eq(incantation->players->len, 2);

    incantation_free(incantation);
    player_free(player1);
    player_free(player2);
}

Test(incantation_tests, add_null_player_to_incantation)
{
    incantation_t *incantation = incantation_new(7);

    cr_assert_eq(incantation->players->len, 0);
    cr_assert_eq(incantation_add_player(incantation, NULL), false);
    cr_assert_eq(incantation->players->len, 0);
    incantation_free(incantation);
}

Test(incantation_tests, add_player_fail_due_to_malloc)
{
    player_t *player1 = player_new(NULL, NULL, (vector2u_t) { 1, 1 });
    incantation_t *incantation = incantation_new(7);

    clcc_return_now(malloc, NULL);
    cr_assert_eq(incantation_add_player(incantation, player1), false);
    clcc_disable_control(malloc);

    incantation_free(incantation);
    player_free(player1);
}

Test(incantation_tests, simple_remove_player)
{
    player_t *player1 = player_new(NULL, NULL, (vector2u_t) { 1, 1 });
    incantation_t *incantation = incantation_new(7);

    cr_assert_eq(incantation->players->len, 0);
    incantation_add_player(incantation, player1);
    cr_assert_eq(incantation->players->len, 1);
    incantation_remove_player(incantation, player1);
    cr_assert_eq(incantation->players->len, 0);

    incantation_free(incantation);
    player_free(player1);
}

Test(incantation_tests, simple_remove_player_requester)
{
    player_t *player1 = player_new(NULL, NULL, (vector2u_t) { 1, 1 });
    player_t *player2 = player_new(NULL, NULL, (vector2u_t) { 1, 1 });
    incantation_t *incantation = incantation_new(7);

    incantation_add_player(incantation, player1);
    incantation->requester = player1;
    cr_assert_eq(incantation->players->len, 1);
    cr_assert_eq(incantation->requester, player1);
    incantation_add_player(incantation, player2);
    cr_assert_eq(incantation->players->len, 2);
    incantation_remove_player(incantation, player1);
    cr_assert_eq(incantation->players->len, 1);
    cr_assert_null(incantation->requester);

    incantation_free(incantation);
    player_free(player1);
    player_free(player2);
}

Test(incantation_tests, remove_non_participant_player)
{
    player_t *player1 = player_new(NULL, NULL, (vector2u_t) { 1, 1 });
    player_t *player2 = player_new(NULL, NULL, (vector2u_t) { 1, 1 });
    player_t *player3 = player_new(NULL, NULL, (vector2u_t) { 1, 1 });
    incantation_t *incantation = incantation_new(7);

    incantation_add_player(incantation, player1);
    incantation->requester = player1;
    cr_assert_eq(incantation->players->len, 1);
    cr_assert_eq(incantation->requester, player1);
    incantation_add_player(incantation, player2);
    cr_assert_eq(incantation->players->len, 2);
    incantation_remove_player(incantation, player3);
    cr_assert_eq(incantation->players->len, 2);

    incantation_free(incantation);
    player_free(player1);
    player_free(player2);
    player_free(player3);
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
    incantation = incantation_start(player, world);
    cr_assert_not_null(incantation);
    cr_assert_eq(incantation->players->len, 2);
    cr_assert_eq(incantation_end(incantation, world), true);
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
    incantation = incantation_start(player, world);
    cr_assert_not_null(incantation);
    cr_assert_eq(incantation->players->len, 1);
    cell->resources[RES_LINEMATE] = 0;
    cr_assert_eq(incantation_end(incantation, world), false);
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
    cr_assert_null(incantation_start(player, world));
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
    incantation = incantation_start(player, world);
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
    incantation = incantation_start(player, world);
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
    incantation = incantation_start(player, world);
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
    incantation = incantation_start(player, world);
    cr_assert_not_null(incantation);
    cr_assert_eq(incantation->players->len, 2);
    cr_assert_eq(incantation_end(incantation, world), true);
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
