/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/world/player.h"

Test(player_new_tests, simple_new)
{
    vector2u_t position = { 10, 5 };
    team_t *team = team_new("Team1", 1);
    player_t *player = player_new(NULL, team, position);

    cr_assert_eq(player->team, team);
    cr_assert_eq(player->position.x, 10);
    cr_assert_eq(player->position.y, 5);
    cr_assert_eq(player->lives, 160);
    cr_assert_eq(player->level, 1);
    cr_assert_null(player->controller);
    player_free(player);
    team_free(team);
}

Test(player_new_tests, new_player_with_malloc_fail)
{
    vector2u_t position = { 10, 5 };
    team_t *team = team_new("Team1", 1);

    clcc_return_now(calloc, NULL);
    cr_assert_null(player_new(NULL, team, position));
    clcc_disable_control(calloc);
}

Test(player_new_tests, free_list_of_players)
{
    vector2u_t position = { 10, 5 };
    team_t *team = team_new("Team1", 1);
    player_t *player = NULL;
    list_t *players = list_new();

    cr_assert_eq(players->len, 0);
    for (int i = 0; i < 10; i++) {
        player = player_new(NULL, team, position);
        list_push(players, NODE_DATA_FROM_PTR(player));
        cr_assert_eq(players->len, i + 1);
    }
    cr_assert_eq(players->len, 10);
    list_clear(players, &player_free_as_node_data);
    cr_assert_eq(players->len, 0);
    list_free(players, NULL);
    team_free(team);
}
