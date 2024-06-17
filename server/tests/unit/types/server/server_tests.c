/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** list_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include "clcc/modules/sys/socket.h"
#include "clcc/modules/stdlib.h"
#include "clcc/modules/unistd.h"
#include "types/server.h"

Test(server_tests, init_server)
{
    server_t server;

    server_init(&server);
    cr_assert_eq(server.socket, -1);
    cr_assert_eq(server.fd_actual.max, -1);
    cr_assert_eq(server.fd_watch.max, -1);
    cr_assert_eq(server.address.sin_family, AF_INET);
    cr_assert_eq(server.address.sin_addr.s_addr, INADDR_ANY);
}

Test(server_tests, new_server)
{
    server_t *server = server_new();

    cr_assert_not_null(server);
    cr_assert_not_null(server->controllers);
    cr_assert_eq(server->socket, -1);
    cr_assert_eq(server->fd_actual.max, -1);
    cr_assert_eq(server->fd_watch.max, -1);
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

Test(server_tests, server_simple_free)
{
    server_t *server = server_new();

    server_free(server);
}

Test(server_tests, server_free_null)
{
    server_free(NULL);
}


Test(server_setup_socket_tests, simple_setup)
{
    // Arrange
    server_t server;

    // Act and assert
    cr_assert(server_setup_socket(&server));
    cr_assert_neq(server.socket, -1);
    cr_assert_neq(fcntl(server.socket, F_GETFD), -1);

    // Cleanup
    close(server.socket);
}

Test(server_setup_socket_tests, setup_null_server)
{
    // Act and assert
    cr_assert_not(server_setup_socket(NULL));
}

Test(server_setup_socket_tests, setup_socket_error_du_to_socket, .init=cr_redirect_stderr)
{
    // Arrange
    server_t server;

    server_init(&server);
    clcc_return_now(socket, -1);

    // Act and assert
    cr_assert_not(server_setup_socket(&server));

    // Cleanup
    clcc_disable_control(socket);
}

Test(server_setup_socket_tests, setup_socket_error_du_to_setsockopt, .init=cr_redirect_stderr)
{
    // Arrange
    server_t server;

    server_init(&server);
    clcc_return_now(setsockopt, -1);

    // Act and assert
    cr_assert_not(server_setup_socket(&server));

    // Cleanup
    clcc_disable_control(setsockopt);
    close(server.socket);
}

Test(server_setup_address_tests, simple_setup)
{
    // Arrange
    server_t server;

    server_init(&server);
    server_setup_socket(&server);

    // Act and assert
    cr_assert(server_setup_address(&server, 4242));
    cr_assert_eq(server.address.sin_family, AF_INET);
    cr_assert_eq(server.address.sin_addr.s_addr, INADDR_ANY);
    cr_assert_eq(server.address.sin_port, htons(4242));

    // Cleanup
    close(server.socket);
}

Test(server_setup_address_tests, setup_null_server)
{
    // Act and assert
    cr_assert_not(server_setup_address(NULL, 4242));
}

Test(server_setup_address_tests, setup_error_du_to_bind, .init=cr_redirect_stderr)
{
    // Arrange
    server_t server;

    server_init(&server);
    clcc_return_now(bind, -1);

    // Act and assert
    cr_assert_not(server_setup_address(&server, 4242));

    // Cleanup
    clcc_disable_control(bind);
}

Test(server_setup_listener_tests, simple_setup)
{
    // Arrange
    server_t server;

    server_init(&server);
    server_setup_socket(&server);
    server_setup_address(&server, 4242);

    // Act and assert
    cr_assert(server_setup_listener(&server));

    // Cleanup
    close(server.socket);
}

Test(server_setup_listener_tests, setup_on_null_server, .init=cr_redirect_stderr)
{
    // Act and assert
    cr_assert_not(server_setup_listener(NULL));
}

Test(server_setup_listener_tests, setup_error_du_to_listen, .init=cr_redirect_stderr)
{
    // Arrange
    server_t server;

    server_init(&server);
    clcc_return_now(listen, -1);

    // Act and assert
    cr_assert_not(server_setup_listener(&server));

    // Cleanup
    clcc_disable_control(listen);
}

Test(server_start_tests, simple_setup)
{
    // Arrange
    server_t server;

    // Act and assert
    server_init(&server);
    cr_assert(server_start(&server, 4242));
    cr_assert(FD_ISSET(server.socket, &server.fd_watch.readable));
    cr_assert_not(FD_ISSET(server.socket, &server.fd_watch.writable));
    cr_assert(FD_ISSET(server.socket, &server.fd_watch.except));

    // Cleanup
    close(server.socket);
}

Test(server_start_tests, setup_null_server)
{
    // Act and assert
    cr_assert_not(server_start(NULL, 4242));
}

Test(server_start_tests, setup_error_du_to_socket, .init=cr_redirect_stderr)
{
    // Arrange
    server_t server;

    server_init(&server);
    clcc_return_now(socket, -1);

    // Act and assert
    cr_assert_not(server_start(&server, 4242));

    // Cleanup
    clcc_disable_control(socket);
}

Test(server_start_tests, setup_error_du_to_setsockopt, .init=cr_redirect_stderr)
{
    // Arrange
    server_t server;

    server_init(&server);
    clcc_return_now(setsockopt, -1);

    // Act and assert
    cr_assert_not(server_start(&server, 4242));

    // Cleanup
    clcc_disable_control(setsockopt);
}

Test(server_start_tests, setup_error_du_to_bind, .init=cr_redirect_stderr)
{
    // Arrange
    server_t server;

    server_init(&server);
    clcc_return_now(bind, -1);

    // Act and assert
    cr_assert_not(server_start(&server, 4242));

    // Cleanup
    clcc_disable_control(bind);
}

Test(server_start_tests, setup_error_du_to_listen, .init=cr_redirect_stderr)
{
    // Arrange
    server_t server;

    server_init(&server);
    clcc_return_now(listen, -1);

    // Act and assert
    cr_assert_not(server_start(&server, 4242));

    // Cleanup
    clcc_disable_control(listen);
}
