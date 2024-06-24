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
    cr_assert_eq(player->position.y, 3);
    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    player_forward(player,world->map);
    cr_assert_eq(player->position.x, 5);
    cr_assert_eq(player->position.y, 3);
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

    player->position = (vector2u_t) { 4, 4 };
    player->inventory[RES_FOOD] = 1;
    player->lives = PLAYER_LIFE_UNITS_PER_FOOD;
    world_register_player(world, player, team);
    map_add_resource(world->map, position, RES_FOOD, 1);
    cr_assert_eq(player_take_object(player, world->map, RES_FOOD), true);
    cr_assert_eq(world->map->cells[4][4].resources[RES_FOOD], 0);
    cr_assert_eq(player->inventory[RES_FOOD], 2);
    cr_assert_eq(player_take_object(player, world->map, RES_LINEMATE), false);
    cr_assert_eq(world->map->cells[4][4].resources[RES_FOOD], 0);
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

    player->position = (vector2u_t) { 4, 4 };
    world_register_player(world, player, team);
    player->inventory[RES_FOOD] = 1;
    player->lives = PLAYER_LIFE_UNITS_PER_FOOD;
    cr_assert_eq(player_set_object(player, world->map, RES_FOOD), true);
    cr_assert_eq(world->map->cells[4][4].resources[RES_FOOD], 1);
    cr_assert_eq(player->inventory[RES_FOOD], 0);
    cr_assert_float_eq(player->lives, 0.0f, 0.0001f, "Player lives: %f", player->lives);
    cr_assert_eq(player_set_object(player, world->map, RES_LINEMATE), false);
    cr_assert_eq(world->map->cells[4][4].resources[RES_LINEMATE], 0);
    cr_assert_eq(player->inventory[RES_LINEMATE], 0);
    player->inventory[RES_LINEMATE] = 1;
    cr_assert_eq(player_set_object(player, world->map, RES_LINEMATE), true);
    cr_assert_eq(world->map->cells[4][4].resources[RES_LINEMATE], 1);
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

Test(player_look_tests, simple_south_look)
{
    map_t *map = map_new((vector2u_t){10, 10});
    player_t *player = player_new(3);
    char *res = NULL;

    cr_assert_not_null(map);
    player->position = (vector2u_t){5, 5};
    map->cells[5][5].resources[RES_FOOD] = 1;
    map->cells[6][6].resources[RES_FOOD] = 2;
    map->cells[6][5].resources[RES_FOOD] = 1;
    map->cells[6][4].resources[RES_FOOD] = 3;
    map->cells[6][4].players->len = 1;
    map->cells[7][5].players->len = 1;
    player->level = 3;
    player->direction = DIR_SOUTH;
    res = player_look(player, map);
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "[food ,food food ,food ,food food food player ,,,player ,,,]");
    free(res);
    map_free(map);
    player_free(player);
}

Test(player_look_tests, simple_north_look)
{
    map_t *map = map_new((vector2u_t){10, 10});
    player_t *player = player_new(3);
    char *res = NULL;

    cr_assert_not_null(map);
    player->position = (vector2u_t){5, 5};
    map->cells[5][5].resources[RES_FOOD] = 1;
    map->cells[4][4].resources[RES_FOOD] = 2;
    map->cells[4][5].resources[RES_FOOD] = 1;
    map->cells[4][6].resources[RES_FOOD] = 3;
    map->cells[4][6].players->len = 1;
    map->cells[3][5].players->len = 1;
    player->level = 3;
    player->direction = DIR_NORTH;
    res = player_look(player, map);
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "[food ,food food ,food ,food food food player ,,,player ,,,]");
    free(res);
    map_free(map);
    player_free(player);
}

Test(player_look_tests, simple_west_look)
{
    map_t *map = map_new((vector2u_t){10, 10});
    player_t *player = player_new(3);
    char *res = NULL;

    cr_assert_not_null(map);
    player->position = (vector2u_t){5, 5};
    map->cells[5][5].resources[RES_FOOD] = 1;
    map->cells[6][4].resources[RES_FOOD] = 2;
    map->cells[5][4].resources[RES_FOOD] = 1;
    map->cells[4][4].resources[RES_FOOD] = 3;
    map->cells[4][4].players->len = 1;
    map->cells[5][3].players->len = 1;
    player->level = 3;
    player->direction = DIR_WEST;
    res = player_look(player, map);
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "[food ,food food ,food ,food food food player ,,,player ,,,]");
    free(res);
    map_free(map);
    player_free(player);
}

Test(player_look_tests, simple_east_look)
{
    map_t *map = map_new((vector2u_t){10, 10});
    player_t *player = player_new(3);
    char *res = NULL;

    cr_assert_not_null(map);
    player->position = (vector2u_t){5, 5};
    map->cells[5][5].resources[RES_FOOD] = 1;
    map->cells[4][6].resources[RES_FOOD] = 2;
    map->cells[5][6].resources[RES_FOOD] = 1;
    map->cells[6][6].resources[RES_FOOD] = 3;
    map->cells[6][6].players->len = 1;
    map->cells[5][7].players->len = 1;
    player->level = 3;
    player->direction = DIR_EAST;
    res = player_look(player, map);
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "[food ,food food ,food ,food food food player ,,,player ,,,]");
    free(res);
    map_free(map);
    player_free(player);
}

Test(player_look_tests, simple_look_with_null_map)
{
    player_t *player = player_new(3);
    char *res = NULL;

    player->position = (vector2u_t){5, 5};
    player->level = 3;
    player->direction = DIR_WEST;
    res = player_look(player, NULL);
    cr_assert_null(res);
    player_free(player);
}

Test(player_look_tests, north_look_out_of_bounds)
{
    map_t *map = map_new((vector2u_t){10, 10});
    player_t *player = player_new(3);
    char *res = NULL;

    cr_assert_not_null(map);
    player->position = (vector2u_t){5, 2};
    map->cells[2][5].resources[RES_FOOD] = 1;
    map->cells[0][3].resources[RES_DERAUMERE] = 1;
    map->cells[6][0].eggs->len = 1;
    map->cells[6][0].players->len = 1;
    map->cells[8][7].resources[RES_FOOD] = 2;
    map->cells[8][7].resources[RES_LINEMATE] = 1;
    map->cells[8][7].resources[RES_DERAUMERE] = 1;
    map->cells[8][7].resources[RES_SIBUR] = 1;
    map->cells[6][9].eggs->len = 1;
    map->cells[6][9].resources[RES_FOOD] = 1;
    map->cells[0][7].resources[RES_FOOD] = 1;
    map->cells[7][8].resources[RES_FOOD] = 1;
    map->cells[9][3].players->len = 3;
    player->level = 7;
    player->direction = DIR_NORTH;
    res = player_look(player, map);
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "[food ,,,,deraumere ,,,,food ,,player player player ,,,,,,,,,,,,food food linemate deraumere sibur ,,,,,,,,,,,food ,,,food egg ,player egg ,,,,,,,,,food egg ,player egg ,,]");
    free(res);
    map_free(map);
    player_free(player);
}

Test(player_look_tests, cell_stats_malloc_fail)
{
    map_t *map = map_new((vector2u_t){10, 10});
    player_t *player = player_new(3);
    char *res = NULL;

    cr_assert_not_null(map);
    player->position = (vector2u_t){5, 5};
    map->cells[5][5].resources[RES_FOOD] = 1;
    map->cells[6][6].resources[RES_FOOD] = 2;
    map->cells[5][6].resources[RES_FOOD] = 1;
    map->cells[4][6].resources[RES_FOOD] = 3;
    map->cells[4][6].players->len = 1;
    map->cells[5][7].players->len = 1;
    player->level = 3;
    player->direction = DIR_EAST;
    clcc_return_now(calloc, NULL);
    res = player_look(player, map);
    cr_assert_null(res);
    map_free(map);
    player_free(player);
}