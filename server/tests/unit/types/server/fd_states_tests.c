/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** connection_tests.c
*/

#include <criterion/criterion.h>
#include "types/server.h"

Test(fd_states_tests, init_fd_states)
{
    fd_states_t states;

    fd_states_init(&states);
    cr_assert_eq(states.max, -1);
    cr_assert_not(FD_ISSET(0, &states.readable));
    cr_assert_not(FD_ISSET(0, &states.writable));
    cr_assert_not(FD_ISSET(0, &states.except));
}

Test(fd_states_tests, set_fd_states_r)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_R);
    cr_assert(FD_ISSET(12, &states.readable));
    cr_assert_not(FD_ISSET(12, &states.writable));
    cr_assert_not(FD_ISSET(12, &states.except));
    cr_assert_eq(states.max, 12);
}

Test(fd_states_tests, set_fd_states_r_and_erase_old_max)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_R);
    cr_assert(FD_ISSET(12, &states.readable));
    cr_assert_not(FD_ISSET(12, &states.writable));
    cr_assert_not(FD_ISSET(12, &states.except));
    cr_assert_eq(states.max, 12);
    fd_states_set(&states, 63, FD_STATES_R);
    cr_assert(FD_ISSET(63, &states.readable));
    cr_assert_not(FD_ISSET(63, &states.writable));
    cr_assert_not(FD_ISSET(63, &states.except));
    cr_assert_eq(states.max, 63);
}

Test(fd_states_tests, set_fd_states_w)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_W);
    cr_assert(FD_ISSET(12, &states.writable));
    cr_assert_not(FD_ISSET(12, &states.readable));
    cr_assert_not(FD_ISSET(12, &states.except));
    cr_assert_eq(states.max, 12);
}

Test(fd_states_tests, set_fd_states_w_and_erase_old_max)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_W);
    cr_assert(FD_ISSET(12, &states.writable));
    cr_assert_not(FD_ISSET(12, &states.readable));
    cr_assert_not(FD_ISSET(12, &states.except));
    cr_assert_eq(states.max, 12);
    fd_states_set(&states, 63, FD_STATES_W);
    cr_assert(FD_ISSET(63, &states.writable));
    cr_assert_not(FD_ISSET(63, &states.readable));
    cr_assert_not(FD_ISSET(63, &states.except));
    cr_assert_eq(states.max, 63);
}

Test(fd_states_tests, set_fd_states_e)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_E);
    cr_assert(FD_ISSET(12, &states.except));
    cr_assert_not(FD_ISSET(12, &states.readable));
    cr_assert_not(FD_ISSET(12, &states.writable));
    cr_assert_eq(states.max, 12);
}

Test(fd_states_tests, set_fd_states_e_and_erase_old_max)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_E);
    cr_assert(FD_ISSET(12, &states.except));
    cr_assert_not(FD_ISSET(12, &states.readable));
    cr_assert_not(FD_ISSET(12, &states.writable));
    cr_assert_eq(states.max, 12);
    fd_states_set(&states, 63, FD_STATES_E);
    cr_assert(FD_ISSET(63, &states.except));
    cr_assert_not(FD_ISSET(63, &states.readable));
    cr_assert_not(FD_ISSET(63, &states.writable));
    cr_assert_eq(states.max, 63);
}

Test(fd_states_tests, set_fd_states_r_w_e_separatly)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_R);
    cr_assert(FD_ISSET(12, &states.readable));
    cr_assert_not(FD_ISSET(12, &states.writable));
    cr_assert_not(FD_ISSET(12, &states.except));
    cr_assert_eq(states.max, 12);
    fd_states_set(&states, 63, FD_STATES_W);
    cr_assert(FD_ISSET(63, &states.writable));
    cr_assert_not(FD_ISSET(63, &states.readable));
    cr_assert_not(FD_ISSET(63, &states.except));
    cr_assert_eq(states.max, 63);
    fd_states_set(&states, 42, FD_STATES_E);
    cr_assert(FD_ISSET(42, &states.except));
    cr_assert_not(FD_ISSET(42, &states.readable));
    cr_assert_not(FD_ISSET(42, &states.writable));
    cr_assert_eq(states.max, 63);
}

Test(fd_states_tests, set_fd_states_r_w_e_together)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_R | FD_STATES_W | FD_STATES_E);
    cr_assert(FD_ISSET(12, &states.readable));
    cr_assert(FD_ISSET(12, &states.writable));
    cr_assert(FD_ISSET(12, &states.except));
    cr_assert_eq(states.max, 12);
}

Test(fd_states_tests, unset_fd_states_r)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_R);
    cr_assert(FD_ISSET(12, &states.readable));
    cr_assert_eq(states.max, 12);
    fd_states_unset(&states, 12, FD_STATES_R);
    cr_assert_not(FD_ISSET(12, &states.readable));
    cr_assert_eq(states.max, -1);
}

Test(fd_states_tests, unset_fd_states_w)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_W);
    cr_assert(FD_ISSET(12, &states.writable));
    cr_assert_eq(states.max, 12);
    fd_states_unset(&states, 12, FD_STATES_W);
    cr_assert_not(FD_ISSET(12, &states.writable));
    cr_assert_eq(states.max, -1);
}

Test(fd_states_tests, unset_fd_states_e)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_E);
    cr_assert(FD_ISSET(12, &states.except));
    cr_assert_eq(states.max, 12);
    fd_states_unset(&states, 12, FD_STATES_E);
    cr_assert_not(FD_ISSET(12, &states.except));
    cr_assert_eq(states.max, -1);
}

Test(fd_states_tests, set_negative_fd)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, -1, FD_STATES_E);
    cr_assert_eq(states.max, -1);
}

Test(fd_states_tests, unset_negative_fd)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_unset(&states, -1, FD_STATES_E);
    cr_assert_eq(states.max, -1);
}

Test(fd_states_tests, unset_fd_states_w_not_max)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_W);
    cr_assert(FD_ISSET(12, &states.writable));
    cr_assert_eq(states.max, 12);
    fd_states_set(&states, 64, FD_STATES_W);
    cr_assert(FD_ISSET(64, &states.writable));
    cr_assert_eq(states.max, 64);
    fd_states_unset(&states, 12, FD_STATES_W);
    cr_assert_not(FD_ISSET(12, &states.writable));
    cr_assert_eq(states.max, 64);
}

Test(fd_states_tests, unset_fd_states_was_max_in_r)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_R);
    cr_assert(FD_ISSET(12, &states.readable));
    cr_assert_eq(states.max, 12);
    fd_states_set(&states, 64, FD_STATES_R);
    cr_assert(FD_ISSET(64, &states.readable));
    cr_assert_eq(states.max, 64);
    fd_states_unset(&states, 64, FD_STATES_R);
    cr_assert_not(FD_ISSET(64, &states.readable));
    cr_assert_eq(states.max, 12);
}

Test(fd_states_tests, unset_fd_states_was_max_in_w)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_W);
    cr_assert(FD_ISSET(12, &states.writable));
    cr_assert_eq(states.max, 12);
    fd_states_set(&states, 64, FD_STATES_W);
    cr_assert(FD_ISSET(64, &states.writable));
    cr_assert_eq(states.max, 64);
    fd_states_unset(&states, 64, FD_STATES_W);
    cr_assert_not(FD_ISSET(64, &states.writable));
    cr_assert_eq(states.max, 12);
}

Test(fd_states_tests, unset_fd_states_was_max_in_e)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_E);
    cr_assert(FD_ISSET(12, &states.except));
    cr_assert_eq(states.max, 12);
    fd_states_set(&states, 64, FD_STATES_E);
    cr_assert(FD_ISSET(64, &states.except));
    cr_assert_eq(states.max, 64);
    fd_states_unset(&states, 64, FD_STATES_E);
    cr_assert_not(FD_ISSET(64, &states.except));
    cr_assert_eq(states.max, 12);
}

Test(fd_states_tests, clear_fd_states_rwe)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 12, FD_STATES_R);
    fd_states_set(&states, 64, FD_STATES_W);
    fd_states_set(&states, 42, FD_STATES_E);
    cr_assert(FD_ISSET(12, &states.readable));
    cr_assert(FD_ISSET(64, &states.writable));
    cr_assert(FD_ISSET(42, &states.except));
    cr_assert_eq(states.max, 64);
    fd_states_clear(&states, FD_STATES_R | FD_STATES_W | FD_STATES_E);
    cr_assert_not(FD_ISSET(12, &states.readable));
    cr_assert_not(FD_ISSET(64, &states.writable));
    cr_assert_not(FD_ISSET(42, &states.except));
    cr_assert_eq(states.max, -1);
}

Test(fd_states_tests, clear_just_r_in_which_is_max)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 64, FD_STATES_R);
    fd_states_set(&states, 12, FD_STATES_W);
    fd_states_set(&states, 42, FD_STATES_E);
    cr_assert(FD_ISSET(64, &states.readable));
    cr_assert(FD_ISSET(12, &states.writable));
    cr_assert(FD_ISSET(42, &states.except));
    cr_assert_eq(states.max, 64);
    fd_states_clear(&states, FD_STATES_R);
    cr_assert_not(FD_ISSET(64, &states.readable));
    cr_assert(FD_ISSET(12, &states.writable));
    cr_assert(FD_ISSET(42, &states.except));
    cr_assert_eq(states.max, 42);
}

Test(fd_states_tests, clear_max_present_in_r_and_w)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 64, FD_STATES_R);
    fd_states_set(&states, 64, FD_STATES_W);
    fd_states_set(&states, 42, FD_STATES_E);
    cr_assert(FD_ISSET(64, &states.readable));
    cr_assert(FD_ISSET(64, &states.writable));
    cr_assert(FD_ISSET(42, &states.except));
    cr_assert_eq(states.max, 64);
    fd_states_clear(&states, FD_STATES_R);
    cr_assert_not(FD_ISSET(64, &states.readable));
    cr_assert(FD_ISSET(64, &states.writable));
    cr_assert(FD_ISSET(42, &states.except));
    cr_assert_eq(states.max, 64);
}

Test(fd_states_tests, clear_only_e)
{
    fd_states_t states;

    fd_states_init(&states);
    fd_states_set(&states, 64, FD_STATES_R);
    fd_states_set(&states, 64, FD_STATES_W);
    fd_states_set(&states, 42, FD_STATES_E);
    cr_assert(FD_ISSET(64, &states.readable));
    cr_assert(FD_ISSET(64, &states.writable));
    cr_assert(FD_ISSET(42, &states.except));
    cr_assert_eq(states.max, 64);
    fd_states_clear(&states, FD_STATES_E);
    cr_assert(FD_ISSET(64, &states.readable));
    cr_assert(FD_ISSET(64, &states.writable));
    cr_assert_not(FD_ISSET(42, &states.except));
    cr_assert_eq(states.max, 64);
}
