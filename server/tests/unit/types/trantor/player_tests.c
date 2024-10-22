/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/trantor/player.h"
#include "types/trantor/team.h"
#include "types/trantor/world.h"

Test(player_new_tests, simple_new)
{
    player_t *player = player_new(1);

    cr_assert_eq(player->team, NULL);
    cr_assert_eq(player->position.x, 0);
    cr_assert_eq(player->position.y, 0);
    cr_assert_eq(player->lives, 1260);
    cr_assert_eq(player->level, 1);
    cr_assert_eq(player->direction, PLAYER_DIRECTION_DEFAULT);
    cr_assert_eq(player->id, 1);
    cr_assert_null(player->controller);
    cr_assert_null(player->incantation);
    player_free(player);
}

Test(player_new_tests, new_player_with_malloc_fail)
{
    clcc_return_now(calloc, NULL);
    cr_assert_null(player_new(1));
    clcc_disable_control(calloc);
}

Test(player_new_tests, free_list_of_players)
{
    player_t *player = NULL;
    list_t *players = list_new();

    cr_assert_eq(players->len, 0);
    for (int i = 0; i < 10; i++) {
        player = player_new(1);
        list_push(players, NODE_DATA_FROM_PTR(player));
        cr_assert_eq(players->len, i + 1);
    }
    cr_assert_eq(players->len, 10);
    list_clear(players, &player_free_as_node_data);
    cr_assert_eq(players->len, 0);
    list_free(players, NULL);
}

Test(player_direction_tests, complete_clockwise_rotation)
{
    player_t *player = player_new(1);

    cr_assert_eq(player->direction, PLAYER_DIRECTION_DEFAULT);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    cr_assert_eq(player->direction, DIR_EAST);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    cr_assert_eq(player->direction, DIR_SOUTH);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    cr_assert_eq(player->direction, DIR_WEST);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    cr_assert_eq(player->direction, DIR_NORTH);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    cr_assert_eq(player->direction, DIR_EAST);

    player_free(player);
}

Test(player_direction_tests, change_anticlockwise_rotation)
{
    player_t *player = player_new(1);

    cr_assert_eq(player->direction, PLAYER_DIRECTION_DEFAULT);
    player_change_direction(player, PLAYER_DIRECTION_LEFT_OFFSET);
    cr_assert_eq(player->direction, DIR_WEST);
    player_change_direction(player, PLAYER_DIRECTION_LEFT_OFFSET);
    cr_assert_eq(player->direction, DIR_SOUTH);
    player_change_direction(player, PLAYER_DIRECTION_LEFT_OFFSET);
    cr_assert_eq(player->direction, DIR_EAST);
    player_change_direction(player, PLAYER_DIRECTION_LEFT_OFFSET);
    cr_assert_eq(player->direction, DIR_NORTH);
    player_change_direction(player, PLAYER_DIRECTION_LEFT_OFFSET);
    cr_assert_eq(player->direction, DIR_WEST);

    player_free(player);
}


Test(player_direction_tests, change_direction)
{
    player_t *player = player_new(1);

    cr_assert_eq(player->direction, PLAYER_DIRECTION_DEFAULT);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    cr_assert_eq(player->direction, DIR_EAST);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    cr_assert_eq(player->direction, DIR_SOUTH);
    player_change_direction(player, PLAYER_DIRECTION_LEFT_OFFSET);
    cr_assert_eq(player->direction, DIR_EAST);
    player_change_direction(player, PLAYER_DIRECTION_LEFT_OFFSET);
    cr_assert_eq(player->direction, DIR_NORTH);
    player_change_direction(player, PLAYER_DIRECTION_LEFT_OFFSET);
    cr_assert_eq(player->direction, DIR_WEST);
    player_change_direction(player, PLAYER_DIRECTION_LEFT_OFFSET);
    cr_assert_eq(player->direction, DIR_SOUTH);
    player_change_direction(player, PLAYER_DIRECTION_LEFT_OFFSET);
    cr_assert_eq(player->direction, DIR_EAST);
    player_change_direction(player, 23);
    cr_assert_eq(player->direction, DIR_EAST);
}

Test(player_forward_tests, simple_forward)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);

    player->position = (vector2u_t) { 4, 4 };
    world_register_player(world, player, team);
    player->direction = PLAYER_DIRECTION_DEFAULT;
    player_forward(player,world->map);
    cr_assert_eq(player->position.x, 4);
    cr_assert_eq(player->position.y, 5);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    player_forward(player,world->map);
    cr_assert_eq(player->position.x, 5);
    cr_assert_eq(player->position.y, 5);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    player_forward(player,world->map);
    cr_assert_eq(player->position.x, 5);
    cr_assert_eq(player->position.y, 4);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    player_forward(player,world->map);
    cr_assert_eq(player->position.x, 4);
    cr_assert_eq(player->position.y, 4);
    world_free(world);
    team_free(team);
}

Test(player_forward_tests, simple_forward_with_unfound_player)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);
    player_t *player = player_new(1);

    player->position = (vector2u_t){ 0, 0 };
    player_forward(player,world->map);
    cr_assert_eq(player->position.x, 0);
    cr_assert_eq(player->position.y, 0);
    world_free(world);
}

Test(player_forward_tests, simple_forward_with_null_player)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);

    player_forward(NULL, world->map);
    world_free(world);
}

Test(player_forward_tests, simple_forward_with_null_world)
{
    player_t *player = player_new(1);

    player_forward(player, NULL);
}

Test(player_take_object_tests, take_object)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);
    vector2u_t position = { 4, 4 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);
    size_t prev_res = 0;

    player->position = (vector2u_t) { 4, 4 };
    player->inventory[RES_FOOD] = 1;
    player->lives = PLAYER_LIFE_UNITS_PER_FOOD;
    world_register_player(world, player, team);
    map_add_resource(world->map, position, RES_FOOD, 1);
    prev_res = world->map->cells[4][4].resources[RES_FOOD];
    cr_assert_eq(player_take_object(player, world->map, RES_FOOD), true);
    cr_assert_eq(world->map->cells[4][4].resources[RES_FOOD], prev_res - 1);
    cr_assert_eq(player->inventory[RES_FOOD], 2);
    prev_res = world->map->cells[4][4].resources[RES_LINEMATE];
    cr_assert_eq(player_take_object(player, world->map, RES_LINEMATE), false);
    cr_assert_eq(world->map->cells[4][4].resources[RES_LINEMATE], prev_res);
    cr_assert_eq(player->inventory[RES_LINEMATE], 0);
}

Test(player_take_object_tests, take_object_with_null_map)
{
    player_t *player = player_new(1);

    cr_assert_eq(player_take_object(player, NULL, RES_FOOD), false);
}

Test(player_take_object_tests, take_object_with_null_player)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);

    cr_assert_eq(player_take_object(NULL, world->map, RES_FOOD), false);
    world_free(world);
}

Test(player_set_object_tests, set_object)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);
    size_t prev_res = 0;

    player->position = (vector2u_t) { 4, 4 };
    world_register_player(world, player, team);
    player->inventory[RES_FOOD] = 1;
    player->lives = PLAYER_LIFE_UNITS_PER_FOOD;
    prev_res = world->map->cells[4][4].resources[RES_FOOD];
    cr_assert_eq(player_set_object(player, world->map, RES_FOOD), true);
    cr_assert_eq(world->map->cells[4][4].resources[RES_FOOD], prev_res + 1);
    cr_assert_eq(player->inventory[RES_FOOD], 0);
    cr_assert_float_eq(player->lives, 0.0f, 0.0001f, "Player lives: %f", player->lives);
    prev_res = world->map->cells[4][4].resources[RES_LINEMATE];
    cr_assert_eq(player_set_object(player, world->map, RES_LINEMATE), false);
    cr_assert_eq(world->map->cells[4][4].resources[RES_LINEMATE], prev_res);
    cr_assert_eq(player->inventory[RES_LINEMATE], 0);
    player->inventory[RES_LINEMATE] = 1;
    prev_res = world->map->cells[4][4].resources[RES_LINEMATE];
    cr_assert_eq(player_set_object(player, world->map, RES_LINEMATE), true);
    cr_assert_eq(world->map->cells[4][4].resources[RES_LINEMATE], prev_res + 1);
    cr_assert_eq(player->inventory[RES_LINEMATE], 0);
}

Test(player_set_object_tests, discard_food_until_failure)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);

    world_register_player(world, player, team);
    player->inventory[RES_FOOD] = 1;
    player->lives = PLAYER_LIFE_UNITS_PER_FOOD;
    cr_assert_eq(player_set_object(player, world->map, RES_FOOD), true);
    cr_assert_eq(player_set_object(player,world->map,  RES_FOOD), false);
}

#include <stdio.h>

Test(player_set_object_tests, discard_food_near_death)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);

    world_register_player(world, player, team);
    player->inventory[RES_FOOD] = 0;
    player->lives = 125;
    cr_assert_eq(player_set_object(player, world->map, RES_FOOD), false);
    player->inventory[RES_FOOD] = 1;
    player->lives = 126;
    cr_assert_eq(player_set_object(player, world->map, RES_FOOD), true);
    cr_assert_float_eq(player->lives, 0.0f, 0.0001f);
    cr_assert_eq(player->inventory[RES_FOOD], 0);
}

Test(player_set_object_tests, set_object_with_null_map)
{
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(1);

    cr_assert_eq(player_set_object(player, NULL, RES_FOOD), false);
    team_free(team);
}

Test(player_set_object_tests, set_object_with_null_player)
{
    vector2u_t size = { 6, 6 };
    world_t *world = world_new(size, 100);

    cr_assert_eq(player_set_object(NULL, world->map, RES_FOOD), false);
    world_free(world);
}
