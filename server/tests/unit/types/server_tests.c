/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** list_tests.c
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/server.h"

Test(server_tests, init_server)
{
    server_t server;

    server_init(&server);
    cr_assert_eq(server.socket, -1);
    cr_assert_eq(server.running, false);
    cr_assert_eq(server.fd_actual.max, 0);
    cr_assert_eq(server.fd_watch.max, 0);
    cr_assert_eq(server.address.sin_family, AF_INET);
    cr_assert_eq(server.address.sin_addr.s_addr, INADDR_ANY);
}

Test(server_tests, new_server)
{
    server_t *server = server_new();

    cr_assert_not_null(server);
    cr_assert_not_null(server->controllers);
    cr_assert_not_null(server->events);
    cr_assert_eq(server->socket, -1);
    cr_assert_eq(server->running, false);
    cr_assert_eq(server->fd_actual.max, 0);
    cr_assert_eq(server->fd_watch.max, 0);
    cr_assert_eq(server->address.sin_family, AF_INET);
    cr_assert_eq(server->address.sin_addr.s_addr, INADDR_ANY);
    server_free(server);
}

Test(server_tests, new_server_fail_due_to_calloc)
{
    clcc_return_now(calloc, NULL);
    cr_assert_null(server_new());
    clcc_disable_control(calloc);
}

Test(server_tests, new_server_fail_due_to_controller_list_new)
{
    clcc_enable_control(malloc);
    clcc_return_value_after(malloc, NULL, 0);
    cr_assert_null(server_new());
    clcc_disable_control(malloc);
}

Test(server_tests, new_server_fail_due_to_events_list_new)
{
    clcc_enable_control(malloc);
    clcc_return_value_after(malloc, NULL, 1);
    cr_assert_null(server_new());
    clcc_disable_control(malloc);
}

Test(server_tests, server_simple_free)
{
    server_t *server = server_new();

    server_free(server);
}

Test(server_tests, server_free_null)
{
    server_free(NULL);
}
