/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** connection_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
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
    cr_assert_eq(controller->generic.emissions->bytes, strlen("WELCOME\n"));

    cr_assert_eq(controller->generic.emissions->bytes, 8);
    cr_assert(memcmp(controller->generic.emissions->data, "WELCOME\n", 8) == 0);

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
    clcc_return_value_after(malloc, NULL, 1);
    controller = server_register_client(server, 42);
    clcc_disable_control(malloc);
    cr_assert_null(controller);
    cr_assert_eq(server->controllers->len, 0);
    server_free(server);
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
    cr_assert_eq(controller->generic.emissions->bytes, 8);
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
    server_disconnect_controller(NULL, NULL);
}

Test(server_close_connection_tests, close_null_controller, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();

    // Act and assert
    server_disconnect_controller(server, NULL);
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
    server_disconnect_controller(NULL, controller);
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

    server_disconnect_controller(server, controller);

    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.state, CTRL_DISCONNECTED);
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
    server_disconnect_controller(server, controller2);
    clcc_disable_control(close);

    cr_assert_eq(NODE_TO_PTR(server->controllers->first, controller_t *), controller1);
    cr_assert_eq(NODE_TO_PTR(server->controllers->first->next, controller_t *), controller2);
    cr_assert_eq(NODE_TO_PTR(server->controllers->last, controller_t *), controller3);

    cr_assert_eq(controller1->generic.state, CTRL_CONNECTED);
    cr_assert_eq(controller2->generic.state, CTRL_DISCONNECTED);
    cr_assert_eq(controller3->generic.state, CTRL_CONNECTED);
    cr_assert_eq(server->controllers->len, 3);
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

Test(server_handle_emissions_tests, emit_on_0_controllers)
{
    // Arrange
    server_t *server = server_new();

    // Pre-assert
    cr_assert_eq(server->controllers->len, 0);

    // Act and assert
    server_handle_emissions(server);
    cr_assert_eq(server->controllers->len, 0);

    // Cleanup
    server_free(server);
}

Test(server_handle_emissions_tests, emit_on_1_disconnected_controllers)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = server_register_client(server, 42);

    controller->generic.state = CTRL_DISCONNECTED;

    // Pre-assert
    cr_assert_eq(server->controllers->len, 1);

    // Act and assert
    server_handle_emissions(server);
    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.emissions->bytes, strlen("WELCOME\n"));

    // Cleanup
    server_remove_disconnected_controllers(server);
    server_free(server);
}

Test(server_handle_emissions_tests, emit_on_1_controller_with_emissions)
{
    // Arrange
    int fd[2];
    char buffer[1024] = { 0 };
    ssize_t buff_content_size = 0;
    server_t *server = server_new();
    controller_t *controller = NULL;

    pipe(fd);
    controller = server_register_client(server, fd[1]);

    // Pre-assert
    cr_assert_not_null(controller);
    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.emissions->bytes, strlen("WELCOME\n"));
    cr_assert_not(FD_ISSET(fd[1], &server->fd_watch.writable));

    // Act and assert
    server_update_fd_watch_write(server);
    server->fd_actual = server->fd_watch;
    server_handle_emissions(server);

    buff_content_size = read(fd[0], buffer, 1024);
    cr_assert_eq(buff_content_size, 8);
    cr_assert_str_eq(buffer, "WELCOME\n");

    // Cleanup
    server_close_all_connections(server);
    close(fd[0]);
    server_free(server);
}

Test(server_handle_emissions_tests, emit_on_1_controller_with_no_emissions)
{
    // Arrange
    int fd[2];
    char buffer[1024] = { 0 };
    ssize_t buff_content_size = 0;
    server_t *server = server_new();
    controller_t *controller = NULL;

    pipe(fd);
    controller = server_register_client(server, fd[1]);
    fcntl(fd[0], F_SETFL, O_NONBLOCK);

    // Pre-assert
    cr_assert_not_null(controller);
    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.emissions->bytes, strlen("WELCOME\n"));
    cr_assert_not(FD_ISSET(fd[1], &server->fd_watch.writable));

    // Act and assert

    // First emissions
    server_update_fd_watch_write(server);
    server->fd_actual = server->fd_watch;
    server_handle_emissions(server);

    buff_content_size = read(fd[0], buffer, 1024);
    cr_assert_eq(buff_content_size, 8);
    cr_assert_str_eq(buffer, "WELCOME\n");
    cr_assert_eq(controller->generic.emissions->bytes, 0);

    // Second emissions
    server_handle_emissions(server);
    memset(buffer, 0, 1024);
    buff_content_size = read(fd[0], buffer, 1024);
    cr_assert_eq(buff_content_size, -1);
    cr_assert_eq(errno, EAGAIN);

    // Cleanup
    server_close_all_connections(server);
    close(fd[0]);
    server_free(server);
}

Test(server_handle_emissions_tests, emit_on_2_controller_with_emissions)
{
    // Arrange
    int fd_1[2];
    int fd_2[2];
    char buffer1[1024] = { 0 };
    char buffer2[1024] = { 0 };
    ssize_t buff_content_size1 = 0;
    ssize_t buff_content_size2 = 0;
    server_t *server = server_new();
    controller_t *controller1, *controller2 = NULL;

    pipe(fd_1);
    pipe(fd_2);
    controller1 = server_register_client(server, fd_1[1]);
    controller2 = server_register_client(server, fd_2[1]);
    fcntl(fd_1[0], F_SETFL, O_NONBLOCK);
    fcntl(fd_2[0], F_SETFL, O_NONBLOCK);

    // Pre-assert
    cr_assert_not_null(controller1);

    cr_assert_eq(server->controllers->len, 2);
    cr_assert_eq(controller1->generic.emissions->bytes, strlen("WELCOME\n"));
    cr_assert_eq(controller2->generic.emissions->bytes, strlen("WELCOME\n"));
    cr_assert_not(FD_ISSET(fd_1[1], &server->fd_watch.writable));
    cr_assert_not(FD_ISSET(fd_2[1], &server->fd_watch.writable));

    // Act and assert

    // First emissions
    server_update_fd_watch_write(server);
    server->fd_actual = server->fd_watch;
    server_handle_emissions(server);

    buff_content_size1 = read(fd_1[0], buffer1, 1024);
    cr_assert_eq(buff_content_size1, 8);
    cr_assert_str_eq(buffer1, "WELCOME\n");
    cr_assert_eq(controller1->generic.emissions->bytes, 0);

    buff_content_size2 = read(fd_2[0], buffer2, 1024);
    cr_assert_eq(buff_content_size2, 8);
    cr_assert_str_eq(buffer2, "WELCOME\n");
    cr_assert_eq(controller2->generic.emissions->bytes, 0);

    // Second emissions
    server_handle_emissions(server);
    memset(buffer1, 0, 1024);
    buff_content_size1 = read(fd_1[0], buffer2, 1024);
    cr_assert_eq(buff_content_size1, -1);
    cr_assert_eq(errno, EAGAIN);
    memset(buffer2, 0, 1024);
    buff_content_size2 = read(fd_1[0], buffer2, 1024);
    cr_assert_eq(buff_content_size2, -1);
    cr_assert_eq(errno, EAGAIN);

    // Cleanup
    server_close_all_connections(server);
    close(fd_1[0]);
    close(fd_2[0]);
    server_free(server);
}

Test(server_handle_emissions_tests, emit_on_2_controller_with_emissions_not_ready)
{
    // Arrange
    int fd_1[2];
    int fd_2[2];
    char buffer1[1024] = { 0 };
    char buffer2[1024] = { 0 };
    ssize_t buff_content_size1 = 0;
    ssize_t buff_content_size2 = 0;
    server_t *server = server_new();
    controller_t *controller1, *controller2 = NULL;

    pipe(fd_1);
    pipe(fd_2);
    controller1 = server_register_client(server, fd_1[1]);
    controller2 = server_register_client(server, fd_2[1]);
    fcntl(fd_1[0], F_SETFL, O_NONBLOCK);
    fcntl(fd_2[0], F_SETFL, O_NONBLOCK);

    // Pre-assert
    cr_assert_not_null(controller1);

    cr_assert_eq(server->controllers->len, 2);
    cr_assert_eq(controller1->generic.emissions->bytes, strlen("WELCOME\n"));
    cr_assert_eq(controller2->generic.emissions->bytes, strlen("WELCOME\n"));
    cr_assert_not(FD_ISSET(fd_1[1], &server->fd_watch.writable));
    cr_assert_not(FD_ISSET(fd_2[1], &server->fd_watch.writable));

    // Act and assert
    server_update_fd_watch_write(server);
    FD_CLR(fd_1[1], &server->fd_watch.writable);
    server->fd_actual = server->fd_watch;
    server_handle_emissions(server);

    buff_content_size1 = read(fd_1[0], buffer1, 1024);
    cr_assert_eq(buff_content_size1, -1);
    cr_assert_eq(errno, EAGAIN);

    buff_content_size2 = read(fd_2[0], buffer2, 1024);
    cr_assert_eq(buff_content_size2, 8);
    cr_assert_str_eq(buffer2, "WELCOME\n");
    cr_assert_eq(controller2->generic.emissions->bytes, 0);

    // Cleanup
    server_close_all_connections(server);
    close(fd_1[0]);
    close(fd_2[0]);
    server_free(server);
}

Test(server_handle_requests_tests, no_requests)
{
    // Arrange
    server_t *server = server_new();

    // Pre-assert
    cr_assert_eq(server->controllers->len, 0);

    // Act and assert
    server_handle_incoming_content(server);
    cr_assert_eq(server->controllers->len, 0);

    // Cleanup
    server_free(server);
}

Test(server_handle_controller_requests_tests, simple_request, .init = cr_redirect_stdout)
{
    // Arrange
    int fds[2];
    server_t *server = server_new();
    controller_t *controller = NULL;
    request_t *request = NULL;

    // Act
    pipe(fds);
    write(fds[1], "HELLO\n", 6);
    controller = server_register_client(server, fds[1]);

    // Assert
    cr_assert_eq(server->controllers->len, 1);
    cr_assert(FD_ISSET(fds[1], &server->fd_watch.readable));
    cr_assert(FD_ISSET(fds[1], &server->fd_watch.except));
    cr_assert_not(FD_ISSET(fds[1], &server->fd_watch.writable));
    cr_assert_eq(server->fd_watch.max, fds[1]);
    cr_assert_not_null(controller);
    cr_assert_eq(controller->generic.requests->len, 0);
    fd_states_set(&server->fd_actual, fds[0], FD_STATES_R);
    controller->generic.socket = fds[0]; // Enable read on the controller

    // Act
    server_handle_controller_incoming_content(server, controller);

    // Assert
    cr_assert_eq(controller->generic.state, CTRL_CONNECTED);
    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.requests->len, 1);
    request = controller_get_last_request(controller);
    cr_assert_not_null(request);
    cr_assert_str_eq(request->buffer, "HELLO");
    cr_assert_eq(request->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(request->content_size, 5);

    // Cleanup
    server_close_all_connections(server);
    close(fds[1]);
    server_free(server);
}

Test(server_handle_controller_requests_tests, no_content_to_read, .init = cr_redirect_stdout)
{
    // Arrange
    int fds[2];
    server_t *server = server_new();
    controller_t *controller = NULL;

    // Act
    pipe(fds);
    controller = server_register_client(server, fds[1]);

    // Assert
    cr_assert_eq(server->controllers->len, 1);
    cr_assert(FD_ISSET(fds[1], &server->fd_watch.readable));
    cr_assert(FD_ISSET(fds[1], &server->fd_watch.except));
    cr_assert_not(FD_ISSET(fds[1], &server->fd_watch.writable));
    cr_assert_eq(server->fd_watch.max, fds[1]);
    cr_assert_not_null(controller);
    cr_assert_eq(controller->generic.requests->len, 0);

    // Act
    server_handle_controller_incoming_content(server, controller);

    // Assert
    cr_assert_eq(controller->generic.state, CTRL_CONNECTED);
    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.requests->len, 0);

    // Cleanup
    server_close_all_connections(server);
    close(fds[0]);
    server_free(server);
}

Test(server_handle_controller_requests_tests, closed_connection, .init = cr_redirect_stdout)
{
    // Arrange
    int fds[2];
    server_t *server = server_new();
    controller_t *controller = NULL;
    request_t *request = NULL;

    // Act
    pipe(fds);
    write(fds[1], "HELLO\n", 6);
    close(fds[1]);
    controller = server_register_client(server, fds[1]);

    // Assert
    cr_assert_eq(server->controllers->len, 1);
    cr_assert(FD_ISSET(fds[1], &server->fd_watch.readable));
    cr_assert(FD_ISSET(fds[1], &server->fd_watch.except));
    cr_assert_not(FD_ISSET(fds[1], &server->fd_watch.writable));
    cr_assert_eq(server->fd_watch.max, fds[1]);
    cr_assert_not_null(controller);
    cr_assert_eq(controller->generic.requests->len, 0);
    fd_states_set(&server->fd_actual, fds[0], FD_STATES_R);
    controller->generic.socket = fds[0]; // Enable read on the controller

    // Read first request
    server_handle_controller_incoming_content(server, controller);
    cr_assert_eq(controller->generic.state, CTRL_CONNECTED);
    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.requests->len, 1);
    request = controller_get_last_request(controller);
    cr_assert_not_null(request);
    cr_assert_str_eq(request->buffer, "HELLO");
    cr_assert_eq(request->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(request->content_size, 5);

    // Act
    server_handle_controller_incoming_content(server, controller);
    cr_assert_eq(controller->generic.state, CTRL_DISCONNECTED);

    // Cleanup
    server_close_all_connections(server);
    server_free(server);
}

Test(server_handle_controller_requests_tests, null_controller, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();

    // Assert
    cr_assert_eq(server->controllers->len, 0);
    server_handle_controller_incoming_content(server, NULL);

    // Cleanup
    server_free(server);
}

Test(server_handle_controller_requests_tests, disconnected_contoller, .init = cr_redirect_stdout)
{
    // Arrange
    server_t *server = server_new();
    controller_t *controller = controller_new(42);

    // Assert
    controller->generic.state = CTRL_DISCONNECTED;
    server_handle_controller_incoming_content(server, controller);

    // Cleanup
    controller_free(controller);
    server_free(server);
}

Test(server_handle_requests_tests, simple_request, .init = cr_redirect_stdout)
{
    // Arrange
    int fds[2];
    server_t *server = server_new();
    controller_t *controller = NULL;
    request_t *request = NULL;

    // Act
    pipe(fds);
    write(fds[1], "HELLO\n", 6);
    controller = server_register_client(server, fds[1]);

    // Assert
    cr_assert_eq(server->controllers->len, 1);
    cr_assert(FD_ISSET(fds[1], &server->fd_watch.readable));
    cr_assert(FD_ISSET(fds[1], &server->fd_watch.except));
    cr_assert_not(FD_ISSET(fds[1], &server->fd_watch.writable));
    cr_assert_eq(server->fd_watch.max, fds[1]);
    cr_assert_not_null(controller);
    cr_assert_eq(controller->generic.requests->len, 0);
    fd_states_set(&server->fd_actual, fds[0], FD_STATES_R);
    controller->generic.socket = fds[0]; // Enable read on the controller

    // Act
    server_handle_incoming_content(server);

    // Assert
    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.requests->len, 1);
    request = controller_get_last_request(controller);
    cr_assert_not_null(request);
    cr_assert_str_eq(request->buffer, "HELLO");
    cr_assert_eq(request->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(request->content_size, 5);

    // Cleanup
    server_close_all_connections(server);
    close(fds[1]);
    server_free(server);
}

Test(server_handle_requests_tests, closed_connection, .init = cr_redirect_stdout)
{
    // Arrange
    int fds[2];
    server_t *server = server_new();
    controller_t *controller = NULL;
    request_t *request = NULL;

    // Act
    pipe(fds);
    close(fds[1]);
    controller = server_register_client(server, fds[1]);

    // Assert
    cr_assert_eq(server->controllers->len, 1);
    cr_assert(FD_ISSET(fds[1], &server->fd_watch.readable));
    cr_assert(FD_ISSET(fds[1], &server->fd_watch.except));
    cr_assert_not(FD_ISSET(fds[1], &server->fd_watch.writable));
    cr_assert_eq(server->fd_watch.max, fds[1]);
    cr_assert_not_null(controller);
    cr_assert_eq(controller->generic.requests->len, 0);
    fd_states_set(&server->fd_actual, fds[0], FD_STATES_R);
    controller->generic.socket = fds[0]; // Enable read on the controller

    // Act
    server_handle_incoming_content(server);

    // Assert
    cr_assert_eq(server->controllers->len, 1);
    cr_assert_eq(controller->generic.state, CTRL_DISCONNECTED);

    // Cleanup
    server_close_all_connections(server);
    server_free(server);
}

Test(server_remove_disconnected_controllers, remove_disconnected_controllers, .init = cr_redirect_stdout)
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
    clcc_return_now(close, 0);
    server_disconnect_controller(server, controller2);
    clcc_disable_control(close);

    cr_assert_eq(controller1->generic.state, CTRL_CONNECTED);
    cr_assert_eq(controller2->generic.state, CTRL_DISCONNECTED);
    cr_assert_eq(controller3->generic.state, CTRL_CONNECTED);

    server_remove_disconnected_controllers(server);

    cr_assert_eq(server->controllers->len, 2);
    cr_assert_eq(NODE_TO_PTR(server->controllers->first, controller_t *), controller1);
    cr_assert_eq(NODE_TO_PTR(server->controllers->last, controller_t *), controller3);

    server_free(server);
}
