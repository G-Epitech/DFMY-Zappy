/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** connection_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "types/server.h"
#include "clcc/modules/stdlib.h"
#include "clcc/modules/unistd.h"
#include "clcc/modules/sys/socket.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
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
    emission_t *emission = NULL;

    // Pre-assert
    cr_assert_eq(server->controllers->len, 0);

    // Act
    controller = server_register_client(server, 42);

    // Assert
    cr_assert_not_null(controller);
    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.socket, 42);
    cr_assert_not_null(controller->generic.emissions);
    cr_assert_not_null(controller->generic.requests);
    cr_assert_eq(controller->generic.emissions->len, 1);

    emission = NODE_TO_PTR(controller->generic.emissions->first, emission_t *);
    cr_assert_not_null(emission);
    cr_assert(memcmp(emission->buffer_ptr->target, "WELCOME", 7) == 0);

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
    cr_assert_eq(controller->generic.emissions->len, 1);
    cr_assert_eq(controller->generic.requests->len, 0);
    cr_assert_eq(controller->generic.type, CTRL_UNKNOWN);
    cr_assert(FD_ISSET(4, &server->fd_watch.readable));
    cr_assert(FD_ISSET(4, &server->fd_watch.except));
    cr_assert_not(FD_ISSET(4, &server->fd_watch.writable));

    // Cleanup
    server_free(server);
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


Test(server_handle_new_connections_tests, no_new_connections)
{
    // Arrange
    server_t *server = server_new();

    // Pre-assert
    cr_assert_eq(server->controllers->len, 0);

    // Act and assert
    server_handle_new_connections(server);
    cr_assert_not(FD_ISSET(server->socket, &server->fd_actual.readable));
    cr_assert_eq(server->controllers->len, 0);

    // Cleanup
    server_free(server);
}

Test(server_handle_new_connections_tests, new_connection, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();

    server->socket = 4;
    fd_states_set(&server->fd_actual, server->socket, FD_STATES_R);

    // Pre-assert
    cr_assert_eq(server->controllers->len, 0);

    // Act and assert
    clcc_return_now(accept, 7);
    server_handle_new_connections(server);
    clcc_disable_control(accept);
    cr_assert(FD_ISSET(server->socket, &(server->fd_actual.readable)));
    cr_assert_eq(server->controllers->len, 1);

    // Cleanup
    server->socket = -1;
    server_free(server);
}

Test(server_close_all_connections_tests, close_no_connections)
{
    // Arrange
    server_t *server = server_new();

    server->socket = 4;

    // Pre-assert
    cr_assert_eq(server->controllers->len, 0);

    // Act and assert
    server_close_all_connections(server);
    cr_assert_eq(server->controllers->len, 0);

    // Cleanup
    server->socket = -1;
    server_free(server);
}

Test(server_close_all_connections_tests, close_2_connections, .init=cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();

    server->socket = 4;

    clcc_return_now(accept, 7);
    server_accept_connection(server);
    clcc_return_now(accept, 8);
    server_accept_connection(server);
    clcc_disable_control(accept);

    // Pre-assert
    cr_assert_eq(server->controllers->len, 2);

    // Act and assert
    clcc_return_now(close, 0);
    server_close_all_connections(server);
    clcc_disable_control(close);
    cr_assert_eq(server->controllers->len, 0);

    // Cleanup
    server_free(server);
}

Test(server_close_all_connections_tests, close_2_connections_and_one_null, .init=cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();

    server->socket = 4;

    clcc_return_now(accept, 7);
    server_accept_connection(server);
    clcc_disable_control(accept);

    list_push(server->controllers, NODE_DATA_FROM_PTR(NULL));

    clcc_return_now(accept, 8);
    server_accept_connection(server);
    clcc_disable_control(accept);

    // Pre-assert
    cr_assert_eq(server->controllers->len, 3);

    // Act and assert
    clcc_return_now(close, 0);
    server_close_all_connections(server);
    clcc_disable_control(close);
    cr_assert_eq(server->controllers->len, 0);

    // Cleanup
    server_free(server);
}
