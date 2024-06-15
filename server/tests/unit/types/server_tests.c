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

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(server_tests, init_server)
{
    server_t server;

    server_init(&server);
    cr_assert_eq(server.socket, -1);
    cr_assert_eq(server.running, false);
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
    cr_assert_eq(server->running, false);
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
    cr_assert(server.running);
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

Test(server_has_pending_connections_tests, no_pending_connections)
{
    // Arrange
    server_t server;

    server_init(&server);

    // Act and assert
    cr_assert_not(server_has_pending_connections(&server));
}

Test(server_has_pending_connections_tests, has_no_pending_connections)
{
    // Arrange
    server_t server;

    server_init(&server);
    FD_SET(server.socket, &server.fd_actual.readable);

    // Act and assert
    cr_assert(server_has_pending_connections(&server));
}

Test(server_has_pending_connections_tests, null_server)
{
    // Act and assert
    cr_assert_not(server_has_pending_connections(NULL));
}

Test(server_has_pending_connections_tests, has_pending_connection)
{
    // Arrange
    server_t server;

    server_init(&server);
    FD_SET(server.socket, &server.fd_actual.readable);

    // Act and assert
    cr_assert(server_has_pending_connections(&server));
}

Test(server_register_client_tests, simple_register) {
    // Arrange
    server_t *server = server_new();
    controller_t *controller = NULL;

    // Act
    cr_assert_eq(server->controllers->len, 0);
    controller = server_register_client(server, 42);
    cr_assert_not_null(controller);
    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.socket, 42);
    cr_assert_not_null(controller->generic.emissions);
    cr_assert_not_null(controller->generic.requests);
    cr_assert_eq(controller->generic.emissions->len, 0);
    cr_assert_eq(controller->generic.requests->len, 0);
    cr_assert_eq(controller->generic.type, CTRL_UNKNOWN);
    cr_assert(FD_ISSET(42, &server->fd_watch.readable));
    cr_assert(FD_ISSET(42, &server->fd_watch.except));
    cr_assert_not(FD_ISSET(42, &server->fd_watch.writable));
    server_free(server);
}

Test(server_register_client_tests, null_server)
{
    // Act and assert
    cr_assert_null(server_register_client(NULL, 42));
}

Test(server_resigter_clients_tests, register_fail_due_to_calloc)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = NULL;


    // Act and assert
    clcc_return_now(calloc, NULL);
    controller = server_register_client(server, 42);
    clcc_disable_control(calloc);
    cr_assert_null(controller);
    cr_assert_eq(server->controllers->len, 0);
    server_free(server);
}

Test(server_register_clients_tests, register_fail_due_to_list_push)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = NULL;

    // Act and assert
    clcc_enable_control(malloc);
    clcc_return_value_after(malloc, NULL, 2);
    controller = server_register_client(server, 42);
    cr_assert_null(controller);
    cr_assert_eq(server->controllers->len, 0);
    server_free(server);
    clcc_disable_control(malloc);
}

Test(server_accept_connection_tests, simple_accept, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = NULL;

    // Act
    clcc_return_now(accept, 4);
    controller = server_accept_connection(server);
    clcc_disable_control(accept);

    // Assert
    cr_assert_not_null(controller);
    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.socket, 4);
    cr_assert_not_null(controller->generic.emissions);
    cr_assert_not_null(controller->generic.requests);
    cr_assert_eq(NODE_TO_PTR(server->controllers->first, controller_t *), controller);
    cr_assert_eq(controller->generic.emissions->len, 0);
    cr_assert_eq(controller->generic.requests->len, 0);
    cr_assert_eq(controller->generic.type, CTRL_UNKNOWN);
    cr_assert(FD_ISSET(4, &server->fd_watch.readable));
    cr_assert(FD_ISSET(4, &server->fd_watch.except));
    cr_assert_not(FD_ISSET(4, &server->fd_watch.writable));
}

Test(server_accept_connection_tests, null_server, .init = cr_redirect_stderr)
{
    // Act and assert
    cr_assert_null(server_accept_connection(NULL));
}

Test(server_accept_connection_tests, accept_fail_due_to_accept, .init = cr_redirect_stderr)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = NULL;

    // Act
    clcc_return_now(accept, -1);
    controller = server_accept_connection(server);
    clcc_disable_control(accept);

    // Assert
    cr_assert_null(controller);
    cr_assert_eq(server->controllers->len, 0);
}

Test(server_accept_connection_tests, accept_fail_due_to_controller_new, .init = cr_redirect_stderr)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = NULL;

    // Act
    clcc_return_now(calloc, NULL);
    clcc_return_now(accept, 4);
    controller = server_accept_connection(server);
    clcc_disable_control(accept);
    clcc_disable_control(calloc);
    cr_assert_null(controller);
    cr_assert_eq(server->controllers->len, 0);
}

Test(server_close_connection_tests, close_null_controller_on_null_server, .init = redirect_all_std)
{
    // Act and assert
    server_close_connection(NULL, NULL);
}

Test(server_close_connection_tests, close_null_controller, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();

    // Act and assert
    server_close_connection(server, NULL);
    cr_assert_eq(server->controllers->len, 0);
    server_free(server);
}

Test(server_close_connection_tests, close_controller_on_null_server, .init = cr_redirect_stdout)
{
    // Arrange
    controller_t *controller = controller_new(42);

    // Act and assert
    cr_assert_eq(controller->generic.socket, 42);
    cr_assert_not_null(controller);
    server_close_connection(NULL, controller);
}

Test(server_close_connection_tests, simple_close, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = NULL;

    // Act
    clcc_return_now(accept, 4);
    controller = server_accept_connection(server);
    clcc_disable_control(accept);

    // Assert
    cr_assert_eq(server->controllers->len, 1);
    cr_assert(FD_ISSET(4, &server->fd_watch.readable));
    cr_assert(FD_ISSET(4, &server->fd_watch.except));
    cr_assert_not(FD_ISSET(4, &server->fd_watch.writable));
    cr_assert_eq(server->fd_watch.max, 4);

    server_close_connection(server, controller);

    cr_assert_eq(server->controllers->len, 0);
    cr_assert_not(FD_ISSET(4, &server->fd_watch.readable));
    cr_assert_not(FD_ISSET(4, &server->fd_watch.except));
    cr_assert_not(FD_ISSET(4, &server->fd_watch.writable));
    cr_assert_eq(server->fd_watch.max, server->socket);
    server_free(server);
}

Test(server_close_connection_tests, simple_close_with_several_clients, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller1, *controller2, *controller3 = NULL;

    // Act
    clcc_return_now(accept, 4);
    controller1 = server_accept_connection(server);
    clcc_return_now(accept, 5);
    controller2 = server_accept_connection(server);
    clcc_return_now(accept, 6);
    controller3 = server_accept_connection(server);
    clcc_disable_control(accept);

    // Assert
    cr_assert_eq(server->controllers->len, 3);
    cr_assert(FD_ISSET(4, &server->fd_watch.readable));
    cr_assert(FD_ISSET(4, &server->fd_watch.except));
    cr_assert_not(FD_ISSET(4, &server->fd_watch.writable));
    cr_assert(FD_ISSET(5, &server->fd_watch.readable));
    cr_assert(FD_ISSET(5, &server->fd_watch.except));
    cr_assert_not(FD_ISSET(5, &server->fd_watch.writable));
    cr_assert(FD_ISSET(6, &server->fd_watch.readable));
    cr_assert(FD_ISSET(6, &server->fd_watch.except));
    cr_assert_not(FD_ISSET(6, &server->fd_watch.writable));
    cr_assert_eq(server->fd_watch.max, 6);

    cr_assert_eq(NODE_TO_PTR(server->controllers->first, controller_t *), controller1);
    cr_assert_eq(NODE_TO_PTR(server->controllers->first->next, controller_t *), controller2);
    cr_assert_eq(NODE_TO_PTR(server->controllers->last, controller_t *), controller3);

    clcc_return_now(close, 0);
    server_close_connection(server, controller2);
    clcc_disable_control(close);

    cr_assert_eq(NODE_TO_PTR(server->controllers->first, controller_t *), controller1);
    cr_assert_eq(NODE_TO_PTR(server->controllers->last, controller_t *), controller3);

    cr_assert_eq(server->controllers->len, 2);
    cr_assert(FD_ISSET(4, &server->fd_watch.readable));
    cr_assert(FD_ISSET(4, &server->fd_watch.except));
    cr_assert_not(FD_ISSET(4, &server->fd_watch.writable));
    cr_assert_not(FD_ISSET(5, &server->fd_watch.readable));
    cr_assert_not(FD_ISSET(5, &server->fd_watch.except));
    cr_assert_not(FD_ISSET(5, &server->fd_watch.writable));
    cr_assert(FD_ISSET(6, &server->fd_watch.readable));
    cr_assert(FD_ISSET(6, &server->fd_watch.except));
    cr_assert_not(FD_ISSET(6, &server->fd_watch.writable));
    cr_assert_eq(server->fd_watch.max, 6);
    cr_assert_eq(server->fd_watch.max, 6);
    server_free(server);
}

Test(server_get_controller_by_socket_tests, get_unknown_controller)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = NULL;

    // Act
    controller = server_get_controller_by_socket(server, 84);

    // Assert
    cr_assert_null(controller);
    server_free(server);
}

Test(server_get_controller_by_socket_tests, get_controller, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = NULL;

    // Act
    clcc_return_now(accept, 4);
    controller = server_accept_connection(server);
    clcc_disable_control(accept);

    // Assert
    cr_assert_not_null(controller);
    cr_assert_eq(server_get_controller_by_socket(server, 4), controller);
    server_free(server);
}

Test(server_get_controller_by_socket_tests, get_controller_with_several_clients, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller1, *controller2, *controller3 = NULL;

    // Act
    clcc_return_now(accept, 4);
    controller1 = server_accept_connection(server);
    clcc_return_now(accept, 5);
    controller2 = server_accept_connection(server);
    clcc_return_now(accept, 6);
    controller3 = server_accept_connection(server);
    clcc_disable_control(accept);

    // Assert
    cr_assert_eq(server_get_controller_by_socket(server, 4), controller1);
    cr_assert_eq(server_get_controller_by_socket(server, 5), controller2);
    cr_assert_eq(server_get_controller_by_socket(server, 6), controller3);
    server_free(server);
}

Test(server_controller_has_content_to_read_tests, has_content, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = NULL;

    // Act
    FD_SET(4, &server->fd_actual.readable);
    clcc_return_now(accept, 4);
    controller = server_accept_connection(server);
    clcc_disable_control(accept);

    // Assert
    cr_assert(server_controller_has_content_to_read(server, controller));
    server_free(server);
}

Test(server_controller_has_content_to_read_tests, no_content, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = NULL;

    // Act
    FD_CLR(4, &server->fd_actual.readable);
    clcc_return_now(accept, 4);
    controller = server_accept_connection(server);
    clcc_disable_control(accept);

    // Assert
    cr_assert_not(server_controller_has_content_to_read(server, controller));
    server_free(server);
}
