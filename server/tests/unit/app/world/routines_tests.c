/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** routines_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "app.h"
#include "clcc/modules/stdlib.h"

Test(world_routine_resource_generation_tests, simple)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    resources_manager_t *res_manager = &world->map->resources_manager;

    for (resource_t i = 0; i < RES_LEN; i++) {
        res_manager->stats[i].actual = 8;
        res_manager->stats[i].limit = 10;
    }
    res_manager->next_generation = 0.0f;
    app_handle_world_routine_resources_generation(world);
    for (resource_t i = 0; i < RES_LEN; i++) {
        cr_assert_eq(res_manager->stats[i].actual, 10);
    }
    cr_assert_eq(res_manager->next_generation, RES_MANAGER_NEXT_GENERATION_DELAY);
    for (resource_t i = 0; i < RES_LEN; i++) {
        res_manager->stats[i].actual = 8;
    }
    app_handle_world_routine_resources_generation(world);
    for (resource_t i = 0; i < RES_LEN; i++) {
        cr_assert_eq(res_manager->stats[i].actual, 8);
    }
    world_free(world);
}

Test(world_routine_team_victory, simple, .init = cr_redirect_stderr)
{
    vector2u_t size = { 10, 10 };
    world_t *world = world_new(size, 100);
    controller_t *ctrl = controller_new(0);
    controller_t *ctrl2 = controller_new(0);
    team_t *team = team_new("Team1", 1);
    server_t *server = server_new();
    player_t *player = player_new(1);
    player_t *player2 = player_new(2);
    player_t *player3 = player_new(3);
    player_t *player4 = player_new(4);
    player_t *player5 = player_new(5);
    player_t *player6 = player_new(6);

    ctrl->generic.type = CTRL_GRAPHIC;
    ctrl2->generic.type = CTRL_PLAYER;
    list_push(server->controllers, NODE_DATA_FROM_PTR(ctrl));
    list_push(server->controllers, NODE_DATA_FROM_PTR(ctrl2));
    list_push(world->teams, NODE_DATA_FROM_PTR(team));
    world_register_player(world, player, team);
    world_register_player(world, player2, team);
    world_register_player(world, player3, team);
    world_register_player(world, player4, team);
    world_register_player(world, player5, team);

    cr_assert_eq(app_handle_world_routine_team_victory(world, server), false);
    world_register_player(world, player6, team);
    cr_assert_eq(app_handle_world_routine_team_victory(world, server), false);
    player->level = 8;
    cr_assert_eq(app_handle_world_routine_team_victory(world, server), false);
    player2->level = 8;
    player3->level = 8;
    player4->level = 8;
    player5->level = 8;
    player6->level = 8;
    cr_assert_eq(app_handle_world_routine_team_victory(world, server), true);

    cr_assert_eq(ctrl->generic.emissions->bytes, 10);
    cr_assert(memcmp(ctrl->generic.emissions->data, "seg Team1\n", 10) == 0);
    cr_assert_eq(ctrl2->generic.emissions->bytes, 0);

    world_free(world);
    server_free(server);
}
