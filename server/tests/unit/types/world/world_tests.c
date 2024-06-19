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
#include "types/world/incantation.h"

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
    incantation_t *incantation = incantation_new(1, player);

    world_add_player(world, player);
    list_push(world->incantations, NODE_DATA_FROM_PTR(incantation));
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
    incantation_t *incantation = incantation_new(1, player2);

    world_add_player(world, player2);
    list_push(world->incantations, NODE_DATA_FROM_PTR(incantation));
    cr_assert_eq(world->next_player_id, 1);
    cr_assert_eq(player->id, 0);
    cr_assert_eq(world->players->len, 1);
    cr_assert_eq(world->incantations->len, 1);
    world_remove_player(world, player);
    cr_assert_eq(world->players->len, 1);
    cr_assert_eq(incantation->players->len, 1);
}

Test(world_routine_resource_generation_tests, simple)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    resources_manager_t *res_manager = &world->resources_manager;

    for (resource_t i = 0; i < RES_LEN; i++) {
        res_manager->stats[i].actual = 8;
        res_manager->stats[i].limit = 10;
    }
    res_manager->next_generation = 0.0f;
    world_routine_resources_generation(world);
    for (resource_t i = 0; i < RES_LEN; i++) {
        cr_assert_eq(res_manager->stats[i].actual, 10);
    }
    cr_assert_eq(res_manager->next_generation, RES_MANAGER_NEXT_GENERATION_DELAY);
    for (resource_t i = 0; i < RES_LEN; i++) {
        res_manager->stats[i].actual = 8;
    }
    world_routine_resources_generation(world);
    for (resource_t i = 0; i < RES_LEN; i++) {
        cr_assert_eq(res_manager->stats[i].actual, 8);
    }
    world_free(world);
}

Test(world_routine_team_victory, simple)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    controller_t *ctrl = controller_new(0);
    controller_t *ctrl2 = controller_new(0);
    team_t *team = team_new("Team1", 1);
    server_t *server = server_new();
    player_t *player = player_new(NULL, team, (vector2u_t){0, 0});
    player_t *player2 = player_new(NULL, team, (vector2u_t){0, 0});
    player_t *player3 = player_new(NULL, team, (vector2u_t){0, 0});
    player_t *player4 = player_new(NULL, team, (vector2u_t){0, 0});
    player_t *player5 = player_new(NULL, team, (vector2u_t){0, 0});
    player_t *player6 = player_new(NULL, team, (vector2u_t){0, 0});


    ctrl->generic.type = CTRL_GRAPHIC;
    ctrl2->generic.type = CTRL_PLAYER;
    list_push(server->controllers, NODE_DATA_FROM_PTR(ctrl));
    list_push(server->controllers, NODE_DATA_FROM_PTR(ctrl2));
    list_push(world->teams, NODE_DATA_FROM_PTR(team));
    world_add_player(world, player);
    world_add_player(world, player2);
    world_add_player(world, player3);
    world_add_player(world, player4);
    world_add_player(world, player5);
    cr_assert_eq(world_routine_team_victory(world, server), false);
    world_add_player(world, player6);
    cr_assert_eq(world_routine_team_victory(world, server), false);
    player->level = 8;
    cr_assert_eq(world_routine_team_victory(world, server), false);
    player2->level = 8;
    player3->level = 8;
    player4->level = 8;
    player5->level = 8;
    player6->level = 8;
    clcc_return_now(malloc, NULL);
    cr_assert_eq(world_routine_team_victory(world, server), true);
    clcc_disable_control(malloc);
    cr_assert_eq(ctrl->generic.emissions->len, 0);
    cr_assert_eq(ctrl2->generic.emissions->len, 0);
    cr_assert_eq(world_routine_team_victory(world, server), true);
    cr_assert_eq(ctrl->generic.emissions->len, 1);
    cr_assert_eq(ctrl2->generic.emissions->len, 0);
    world_free(world);
    server_free(server);
}
