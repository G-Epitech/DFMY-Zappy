/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include "clcc/modules/stdlib.h"
#include "types/trantor/egg.h"
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
    cr_assert_eq(world->dead_players->len, 0);
    cr_assert_eq(world->next_player_id, 0);
    cr_assert_eq(world->next_egg_id, 0);
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
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);

    cr_assert_eq(world_register_player(world, player, team), true);
    cr_assert_eq(world->players->len, 1);
    cr_assert_eq(world->players->first->data.ptr, player);
    world_free(world);
    team_free(team);
}

Test(world_add_player_tests, add_player_to_world_fail_push_world)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);

    clcc_return_now(malloc, NULL);
    cr_assert_eq(world_register_player(world, player, team), false);
    clcc_disable_control(malloc);
    cr_assert_eq(world->players->len, 0);
    world_free(world);
    team_free(team);
}

Test(world_add_player_tests, add_player_to_world_fail_push_world_cell)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);

    clcc_return_value_after(malloc, NULL, 1);
    clcc_enable_control(malloc);
    cr_assert_eq(world_register_player(world, player, team), false);
    clcc_disable_control(malloc);
    world_free(world);
    team_free(team);
}

Test(world_add_player_tests, add_player_to_world_fail_push_world_team)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);

    clcc_return_value_after(malloc, NULL, 2);
    clcc_enable_control(malloc);
    cr_assert_eq(world_register_player(world, player, team), false);
    clcc_disable_control(malloc);
    world_free(world);
    team_free(team);
}

Test(world_remove_player_tests, remove_player_from_everything)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);
    incantation_t *incantation = incantation_new(1, (vector2u_t) { 1, 1 });

    world_register_player(world, player, team);
    list_push(world->incantations, NODE_DATA_FROM_PTR(incantation));
    incantation_add_player(incantation, player);
    cr_assert_eq(world->players->len, 1);
    cr_assert_eq(world->incantations->len, 1);
    world_kill_player(world, player, false);
    cr_assert_eq(world->players->len, 0);
    cr_assert_eq(incantation->players->len, 0);
    cr_assert_eq(world->dead_players->len, 1);
    world_free(world);
}

Test(world_remove_player_tests, remove_unadded_player_from_everything)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);
    player_t *player2 = player_new(2);
    incantation_t *incantation = incantation_new(1, (vector2u_t) { 1, 1 });

    world_register_player(world, player2, team);
    incantation_add_player(incantation, player2);
    list_push(world->incantations, NODE_DATA_FROM_PTR(incantation));
    cr_assert_eq(player->id, 1);
    cr_assert_eq(world->players->len, 1);
    cr_assert_eq(world->incantations->len, 1);
    world_kill_player(world, player, false);
    cr_assert_eq(world->players->len, 1);
    cr_assert_eq(incantation->players->len, 1);
    cr_assert_eq(world->dead_players->len, 0);
}

Test(incantation_tests, sucesful_incantation)
{
    vector2u_t size = { 10, 10 };
    vector2u_t pos = { 1, 1 };
    world_t *world = world_new(size, 2);
    player_t *player = player_new(1);
    player_t *player2 = player_new(1);
    map_cell_t *cell = NULL;
    incantation_t *incantation = NULL;

    player->position = pos;
    player2->position = pos;
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
    cr_assert_eq(incantation_is_valid(incantation, world->map), true);
    cr_assert_eq(incantation_complete_success(incantation, world->map), true);
    world_remove_incantation(world, incantation);
    cr_assert_eq(player->level, 2);
    cr_assert_eq(player2->level, 2);
    cr_assert_eq(cell->resources[RES_LINEMATE], 0);
    world_free(world);
    player_free(player2);
    player_free(player);
}

Test(incantation_tests, calloc_fail)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 2);
    player_t *player = player_new(1);

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
    player_t *player = player_new(1);
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
    player_t *player = player_new(1);
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
    player_t *player = player_new(1);
    player_t *player2 = player_new(1);
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
    player_t *player = player_new(1);
    player_t *player2 = player_new(1);
    player_t *player3 = player_new(1);
    map_cell_t *cell = NULL;
    incantation_t *incantation = NULL;

    cr_assert_not_null(world);
    cell = MAP_CELL_AT_POS(world->map, pos);
    list_push(cell->players, NODE_DATA_FROM_PTR(player));
    list_push(cell->players, NODE_DATA_FROM_PTR(player2));
    list_push(cell->players, NODE_DATA_FROM_PTR(player3));
    cr_assert_not_null(cell);
    cr_assert_eq(cell->players->len, 3);
    player->position = pos;
    player2->position = pos;
    player3->position = pos;
    player->level = 2;
    player2->level = 2;
    player3->level = 1;
    cell->resources[RES_LINEMATE] = 1;
    cell->resources[RES_DERAUMERE] = 1;
    cell->resources[RES_SIBUR] = 1;
    incantation = world_start_incantation(world, player);
    cr_assert_not_null(incantation);
    cr_assert_eq(incantation->players->len, 2);
    cr_assert_eq(incantation_is_valid(incantation, world->map), true);
    cr_assert_eq(incantation_complete_success(incantation, world->map), true);
    world_remove_incantation(world, incantation);
    cr_assert_eq(player->level, 3);
    cr_assert_eq(player2->level, 3);
    cr_assert_eq(player3->level, 1);
    cr_assert_eq(cell->resources[RES_LINEMATE], 0);
    cr_assert_eq(cell->resources[RES_DERAUMERE], 0);
    cr_assert_eq(cell->resources[RES_SIBUR], 0);
    world_free(world);
    player_free(player3);
    player_free(player2);
    player_free(player);
}

Test(world_create_teams_tests, create_2_teams_3_slots)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 2);
    team_t *team1, *team2 = NULL;
    size_t egg_counter = 0;
    char *teams_names[3] = { "Team1", "Team2", NULL };

    cr_assert_not_null(world);
    cr_assert_eq(world_create_teams(world, teams_names, 3), true);
    cr_assert_eq(world->teams->len, 2);
    team1 = NODE_TO_PTR(world->teams->first, team_t *);
    team2 = NODE_TO_PTR(world->teams->first->next, team_t *);

    cr_assert_str_eq(team1->name, "Team1");
    cr_assert_str_eq(team2->name, "Team2");

    for (node_t *node = world->teams->first; node; node = node->next) {
        team_t *team = NODE_TO_PTR(node, team_t *);

        cr_assert_not_null(team);
        cr_assert_eq(team->min_slots, 3);
        cr_assert_eq(team->players->len, 0);
        cr_assert_eq(team->eggs->len, 3);

        for (node_t *egg_node = team->eggs->first; egg_node; egg_node = egg_node->next) {
            egg_t *egg = NODE_TO_PTR(egg_node, egg_t *);

            cr_assert_not_null(egg);
            cr_assert_eq(egg->id, egg_counter);
            cr_assert_eq(egg->team, team);
            egg_counter += 1;
        }
    }
    cr_assert_eq(world->next_egg_id, 6);
    world_free(world);
}

Test(world_hatch_egg_tests, hatch_one_egg)
{
    // Arrange
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 2);
    char *teams_names[] = { "Team1", "Team2", NULL };
    team_t *team = NULL;
    egg_t *egg = NULL;
    vector2u_t egg_pos;
    map_cell_t *cell = NULL;
    int initial_egg_nb_on_cell = 0;
    int initial_egg_nb_in_team = 0;
    player_t *player = NULL;

    world_create_teams(world, teams_names, 2);
    team = NODE_TO_PTR(world->teams->first, team_t *);
    egg = NODE_TO_PTR(team->eggs->first, egg_t *);
    cell = MAP_EGG_CELL(world->map, egg);

    // Pre-asserts
    cr_assert_eq(world->teams->len, 2);
    cr_assert_eq(team->eggs->len, 2);
    cr_assert_eq(cell->players->len, 0);
    cr_assert_not_null(cell);

    // Save initial data
    initial_egg_nb_on_cell = (int) cell->eggs->len;
    initial_egg_nb_in_team = (int) team->eggs->len;

    // Act
    player = world_hatch_egg(world, egg);

    // Assert
    cr_assert_not_null(player);
    cr_assert_eq(cell->players->len, 1);
    cr_assert_eq(cell->eggs->len, initial_egg_nb_on_cell);
    cr_assert_eq(team->eggs->len, initial_egg_nb_in_team);
    cr_assert_eq(NODE_TO_PTR(cell->players->first, player_t *), player);
    cr_assert_eq(player->team, team);
    cr_assert_eq(player->position.x, egg->position.x);
    cr_assert_eq(player->position.y, egg->position.y);
    cr_assert_eq(player->level, 1);
    cr_assert_eq(player->id, 0);
    cr_assert_eq(world->next_player_id, 1);

    // Cleanup
    world_free(world);
}

Test(world_kill_egg_tests, kill_one_egg)
{
    // Arrange
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 2);
    char *teams_names[] = { "Team1", "Team2", NULL };
    team_t *team = NULL;
    egg_t *egg = NULL;
    vector2u_t egg_pos;
    map_cell_t *cell = NULL;
    int initial_egg_nb_on_cell = 0;
    int initial_egg_nb_in_team = 0;

    world_create_teams(world, teams_names, 2);
    team = NODE_TO_PTR(world->teams->first, team_t *);
    egg = NODE_TO_PTR(team->eggs->first, egg_t *);
    cell = MAP_EGG_CELL(world->map, egg);

    // Pre-asserts
    cr_assert_eq(world->teams->len, 2);
    cr_assert_eq(team->eggs->len, 2);
    cr_assert_eq(cell->players->len, 0);
    cr_assert_not_null(cell);

    // Save initial data
    initial_egg_nb_on_cell = (int) cell->eggs->len;
    initial_egg_nb_in_team = (int) team->eggs->len;

    // Act
    world_kill_egg(world, egg);

    // Assert
    cr_assert_eq(cell->eggs->len, initial_egg_nb_on_cell - 1);
    cr_assert_eq(team->eggs->len, initial_egg_nb_in_team - 1);

    // Cleanup
    world_free(world);
}

Test(world_kill_eggs, kill_eggs_list)
{
    // Arrange
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 2);
    char *teams_names[] = { "Team1", "Team2", NULL };
    server_t *server = server_new();
    controller_t *controller = controller_new(0);
    team_t *team = NULL;
    egg_t *egg = NULL;
    vector2u_t egg_pos;
    map_cell_t *cell = NULL;

    controller->generic.type = CTRL_GRAPHIC;
    list_push(server->controllers, NODE_DATA_FROM_PTR(controller));
    world_create_teams(world, teams_names, 2);
    team = NODE_TO_PTR(world->teams->first, team_t *);
    egg = NODE_TO_PTR(team->eggs->first, egg_t *);
    cell = MAP_EGG_CELL(world->map, egg);

    // Pre-asserts
    cr_assert_eq(world->teams->len, 2);
    cr_assert_eq(team->eggs->len, 2);
    cr_assert_eq(cell->players->len, 0);
    cr_assert_not_null(cell);

    // Act
    world_kill_eggs(world, team->eggs, server);

    // Assert
    cr_assert_eq(team->eggs->len, 0);
    cr_assert_eq(cell->eggs->len, 0);
    cr_assert_str_eq(controller->generic.emissions->data, "edi 0\nedi 1\n");

    // Cleanup
    world_free(world);
}
