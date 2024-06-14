/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** incantation_tests.c
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/world/incantation.h"

Test(incantation_tests, new_incantation)
{
    player_controller_t *requester = calloc(1, sizeof(player_controller_t));
    incantation_t *incantation = incantation_new(requester, 1);

    cr_assert_not_null(incantation);
    cr_assert_eq(incantation->level, 1);
    cr_assert_eq(incantation->requester, requester);
    cr_assert_not_null(incantation->players);
    cr_assert_eq(incantation->players->len, 0);
    incantation_free(incantation);
    free(requester);
}

Test(incantation_tests, new_incantation_fail_due_to_calloc)
{
    player_controller_t *requester = calloc(1, sizeof(player_controller_t));

    clcc_return_now(calloc, NULL);
    cr_assert_null(incantation_new(requester, 1));
    clcc_disable_control(calloc);
    free(requester);
}

Test(incantation_tests, new_incantation_fail_due_to_players_list_new)
{
    player_controller_t *requester = calloc(1, sizeof(player_controller_t));

    clcc_return_now(malloc, NULL);
    cr_assert_null(incantation_new(requester, 1));
    clcc_disable_control(malloc);
    free(requester);
}

Test(incantation_tests, free_incantation)
{
    player_controller_t *requester = calloc(1, sizeof(player_controller_t));
    incantation_t *incantation = incantation_new(requester, 1);

    incantation_free(incantation);
    free(requester);
}

Test(incantation_tests, free_null_incantation)
{
    incantation_free(NULL);
}

Test(incantation_tests, free_list_of_incantations)
{
    player_controller_t *requester = calloc(1, sizeof(player_controller_t));
    list_t *incantations = list_new();

    cr_assert_eq(incantations->len, 0);
    for (int i = 0; i < 5; i++) {
        incantation_t *incantation = incantation_new(requester, i);

        cr_assert_not_null(incantation);
        list_push(incantations, NODE_DATA_FROM_PTR(incantation));
        cr_assert_eq(incantations->len, i + 1);
    }
    cr_assert_eq(incantations->len, 5);
    list_clear(incantations, &incantation_free_as_node_data);
    cr_assert_eq(incantations->len, 0);
    list_free(incantations, NULL);
    free(requester);
}


