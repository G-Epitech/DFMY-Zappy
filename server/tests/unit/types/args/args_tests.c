/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "types/args.h"

Test(options_init_tests, simple_init)
{
    args_t args = { 0 };

    args_init(&args);
    cr_assert_eq(args.port, -1);
    cr_assert_eq(args.width, 0);
    cr_assert_eq(args.height, 0);
    cr_assert_eq(args.clients_nb, 0);
    cr_assert_eq(args.frequency, ARGS_DEFAULT_FREQ);
    cr_assert_eq(args.teams, NULL);
}
