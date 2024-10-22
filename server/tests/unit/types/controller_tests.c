/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** list_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <fcntl.h>
#include "clcc/modules/unistd.h"
#include "clcc/modules/stdlib.h"
#include "clcc/modules/sys/socket.h"
#include "types/list.h"
#include "types/controller.h"
#include "types/trantor/player.h"
#include "types/server.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(controller_tests, init_controller)
{
    controller_t controller = { 0 };

    controller_init(&controller, 12);
    cr_assert_eq(controller.generic.type, CTRL_UNKNOWN);
    cr_assert_eq(controller.generic.socket, 12);
    cr_assert_null(controller.generic.requests);
    cr_assert_null(controller.generic.emissions);
}

Test(controller_tests, new_controller)
{
    controller_t *controller = controller_new(0);

    cr_assert_not_null(controller);
    cr_assert_eq(controller->generic.type, CTRL_UNKNOWN);
    cr_assert_eq(controller->generic.socket, 0);
    cr_assert_not_null(controller->generic.requests);
    cr_assert_not_null(controller->generic.emissions);
    controller_free(controller);
}

Test(controller_tests, new_controller_with_calloc_fail)
{
    clcc_return_now(calloc, NULL);
    cr_assert_null(controller_new(0));
    clcc_disable_control(calloc);
}


Test(controller_tests, new_controller_with_requests_alloc_fail)
{
    clcc_enable_control(malloc);
    clcc_return_value_after(malloc, NULL, 0);
    cr_assert_null(controller_new(0));
    clcc_disable_control(malloc);
}

Test(controller_tests, new_controller_with_emissions_alloc_fail)
{
    clcc_enable_control(calloc);
    clcc_return_value_after(calloc, NULL, 1);
    cr_assert_null(controller_new(0));
    clcc_disable_control(calloc);
}

Test(controller_tests, free_controller)
{
    controller_free(NULL);
}

Test(controller_tests, free_list_of_controllers)
{
    list_t list;
    controller_t *controller1 = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);

    list_init(&list);
    cr_assert_eq(list.len, 0);
    list_push(&list, NODE_DATA_FROM_PTR(controller1));
    list_push(&list, NODE_DATA_FROM_PTR(controller2));
    list_push(&list, NODE_DATA_FROM_PTR(controller3));
    cr_assert_eq(list.len, 3);
    list_clear(&list, &controller_free_as_node_data);
    cr_assert_eq(list.len, 0);
}

Test(controller_tests, get_next_pending_request_with_no_request)
{
    controller_t *controller = controller_new(0);
    request_t *req = controller_get_next_pending_request(controller);

    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_PENDING);
    cr_assert_eq(controller->generic.requests->len, 1);
}

Test(controller_tests, get_next_pending_request_with_no_request_but_create_fail_due_to_list_push, .init = cr_redirect_stderr) {
    controller_t *controller = controller_new(0);
    request_t *req = NULL;

    clcc_enable_control(malloc);
    clcc_return_value_after(malloc, NULL, 0);
    controller_get_next_pending_request(controller);
    clcc_disable_control(malloc);
    cr_assert_eq(controller->generic.requests->len, 0);
    cr_assert_null(req);

    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_with_no_request_but_create_fail_due_to_calloc, .init = cr_redirect_stderr) {
    controller_t *controller = controller_new(0);
    request_t *req = NULL;

    clcc_enable_control(calloc);
    clcc_return_value_after(calloc, NULL, 0);
    controller_get_next_pending_request(controller);
    clcc_disable_control(calloc);
    cr_assert_null(req);
    cr_assert_eq(controller->generic.requests->len, 0);

    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_with_request_pending)
{
    controller_t *controller = controller_new(0);
    request_t *req = controller_get_next_pending_request(controller);

    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_PENDING);
    cr_assert_eq(controller_get_next_pending_request(controller), req);
    cr_assert_eq(controller->generic.requests->len, 1);

    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_with_request_ready)
{
    controller_t *controller = controller_new(0);
    request_t *req1 = controller_get_next_pending_request(controller);
    request_t *req2 = NULL;

    cr_assert_eq(controller->generic.requests->len, 1);
    cr_assert_not_null(req1);
    cr_assert_eq(req1->status, REQ_PENDING);
    req1->status = REQ_READY;
    req2 = controller_get_next_pending_request(controller);
    cr_assert_not_null(req2);
    cr_assert_eq(req2->status, REQ_PENDING);
    cr_assert_neq(req1, req2);
    cr_assert_eq(controller->generic.requests->len, 2);
    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_on_player_controller)
{
    controller_t *controller = controller_new(0);
    controller->generic.type = CTRL_PLAYER;
    request_t *req = controller_get_next_pending_request(controller);

    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_PENDING);
    cr_assert_eq(controller->generic.requests->len, 1);

    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_on_player_controller_with_max_requests, .init = cr_redirect_stdout)
{
    controller_t *controller = controller_new(0);
    controller->generic.type = CTRL_PLAYER;

    cr_assert_eq(controller->generic.requests->len, 0);
    for (int i = 0; i < CTRL_PLAYER_MAX_REQ; ++i) {
        request_t *req = controller_get_next_pending_request(controller);
        req->status = REQ_READY;
    }
    cr_assert_eq(controller->generic.requests->len, CTRL_PLAYER_MAX_REQ);

    request_t *req = controller_get_next_pending_request(controller);
    cr_assert_null(req);

    cr_assert_eq(controller->generic.requests->len, CTRL_PLAYER_MAX_REQ);
    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_on_graphic_controller)
{
    controller_t *controller = controller_new(0);
    controller->generic.type = CTRL_GRAPHIC;
    request_t *req = controller_get_next_pending_request(controller);

    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_PENDING);
    cr_assert_eq(controller->generic.requests->len, 1);

    controller_free(controller);
}

Test(controller_tests, controller_read_2_tokens_with_2_newlines)
{
    char buffer[] = "token1\ntoken2\n";
    size_t size = sizeof(buffer) - 1;
    request_token_t token = { 0 };

    cr_assert_eq(controller_read_next_token(buffer, size, &token), false);
    cr_assert_eq(token.size, 7);
    cr_assert_eq(memcmp(token.content, "token1\n", 7), 0);
    cr_assert_eq(controller_read_next_token(buffer + 7, size - 7, &token), true);
    cr_assert_eq(token.size, 7);
    cr_assert_eq(memcmp(token.content, "token2\n", 7), 0);
}

Test(controller_tests, controller_read_2_tokens_with_1_newline)
{
    char buffer[] = "token1\ntoken2";
    size_t size = sizeof(buffer) - 1;
    request_token_t token = { 0 };

    cr_assert_eq(controller_read_next_token(buffer, size, &token), false);
    cr_assert_eq(token.size, 7);
    cr_assert_eq(memcmp(token.content, "token1\n", 7), 0);
    cr_assert_eq(controller_read_next_token(buffer + 7, size - 7, &token), true);
    cr_assert_eq(token.size, 6);
    cr_assert_eq(memcmp(token.content, "token2", 6), 0);
}

Test(controller_tests, controller_handle_buffer_token_complete_req)
{
    controller_t *controller = controller_new(0);
    char buffer[] = "complete request 1\ncomplete request 2\n";
    request_t *req = NULL;
    request_token_t token = {
        .content = buffer,
        .size = 19
    };

    cr_assert_eq(controller->generic.requests->len, 0);
    controller_handle_buffer_token(controller, &token);
    cr_assert_eq(controller->generic.requests->len, 1);
    req = controller_get_last_request(controller);
    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_READY);
    cr_assert_eq(req->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(req->content_size, 18);
    cr_assert_eq(memcmp(req->buffer, buffer, 18), 0);
}

Test(controller_tests, controller_handle_buffer_token_pending_req)
{
    controller_t *controller = controller_new(0);
    char buffer[] = "pending request 1\npending request 2";
    request_t *req = NULL;
    request_token_t token = {
        .content = buffer,
        .size = 18
    };

    cr_assert_eq(controller->generic.requests->len, 0);
    controller_handle_buffer_token(controller, &token);
    cr_assert_eq(controller->generic.requests->len, 1);
    req = controller_get_last_request(controller);
    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_READY);
    cr_assert_eq(req->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(req->content_size, 17);
    cr_assert_eq(memcmp(req->buffer, "pending request 1", 18), 0);

    token.content += token.size;
    token.size = 17;

    controller_handle_buffer_token(controller, &token);
    cr_assert_eq(controller->generic.requests->len, 2);
    req = controller_get_last_request(controller);
    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_PENDING);
    cr_assert_eq(req->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(req->content_size, 17);
    cr_assert_eq(memcmp(req->buffer, "pending request 2", 17), 0);

    controller_free(controller);
}

Test(controller_tests, controller_handle_buffer_token_create_request_fail, .init = cr_redirect_stderr)
{
    controller_t *controller = controller_new(0);
    char buffer[] = "pending request 1\npending request 2";
    request_t *req = NULL;
    request_token_t token = {
        .content = buffer,
        .size = 18
    };

    clcc_enable_control(calloc);
    clcc_return_value_after(calloc, NULL, 1);
    cr_assert_eq(controller->generic.requests->len, 0);
    controller_handle_buffer_token(controller, &token);
    cr_assert_eq(controller->generic.requests->len, 0);
    clcc_disable_control(calloc);

    controller_free(controller);
}

Test(controller_tests, controller_handle_buffer_token_append_fail, .init = cr_redirect_stderr)
{
    controller_t *controller = controller_new(0);
    char buffer[REQ_BUFF_SIZE];
    request_t *req = NULL;
    request_token_t token = {
        .content = buffer,
        .size = REQ_BUFF_SIZE
    };

    memset(buffer, 'a', REQ_BUFF_SIZE);
    cr_assert_eq(controller->generic.requests->len, 0);
    controller_handle_buffer_token(controller, &token);
    cr_assert_eq(controller->generic.requests->len, 1);

    clcc_enable_control(realloc);
    clcc_return_value_after(realloc, NULL, 0);
    controller_handle_buffer_token(controller, &token);
    clcc_disable_control(realloc);

    controller_free(controller);
}

Test(controller_tests, controller_handle_buffer_with_2_complete_requests)
{
    controller_t *controller = controller_new(0);
    char buffer[REQ_BUFF_SIZE] = "complete request 1\ncomplete request 2\n";
    size_t size = 38;

    cr_assert_eq(controller->generic.requests->len, 0);
    controller_handle_buffer(controller, buffer, size);
    cr_assert_eq(controller->generic.requests->len, 2);

    request_t *req1 = NODE_TO_PTR(controller->generic.requests->first, request_t *);
    request_t *req2 = NODE_TO_PTR(controller->generic.requests->last, request_t *);

    cr_assert_not_null(req1);
    cr_assert_not_null(req2);
    cr_assert_eq(req1->status, REQ_READY);
    cr_assert_eq(req2->status, REQ_READY);
    cr_assert_eq(req1->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(req2->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(req1->content_size, 18);
    cr_assert_eq(req2->content_size, 18);
    cr_assert_eq(memcmp(req1->buffer, "complete request 1", 18), 0);
    cr_assert_eq(memcmp(req2->buffer, "complete request 2", 18), 0);

    controller_free(controller);
}

Test(controller_tests, controller_handle_buffer_with_1_complete_request_and_1_pending_request)
{
    controller_t *controller = controller_new(0);
    char buffer[REQ_BUFF_SIZE] = "complete request 1\npending request 2";
    size_t size = 36;

    cr_assert_eq(controller->generic.requests->len, 0);
    controller_handle_buffer(controller, buffer, size);
    cr_assert_eq(controller->generic.requests->len, 2);

    request_t *req1 = NODE_TO_PTR(controller->generic.requests->first, request_t *);
    request_t *req2 = NODE_TO_PTR(controller->generic.requests->last, request_t *);

    cr_assert_not_null(req1);
    cr_assert_not_null(req2);
    cr_assert_eq(req1->status, REQ_READY);
    cr_assert_eq(req2->status, REQ_PENDING);
    cr_assert_eq(req1->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(req2->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(req1->content_size, 18);
    cr_assert_eq(req2->content_size, 17);
    cr_assert_eq(memcmp(req1->buffer, "complete request 1", 18), 0);
    cr_assert_eq(memcmp(req2->buffer, "pending request 2", 17), 0);

    controller_free(controller);
}

Test(controller_tests, controller_handle_buffer_with_reach_max_requests, .init = cr_redirect_stdout)
{
    controller_t *controller = controller_new(0);
    char buffer[REQ_BUFF_SIZE] = "req1\nreq2\nreq3\nreq4\nreq5\nreq6\nreq7\nreq8\nreq9\nreq10\nreq11\nreq12\nreq13\n";
    size_t size = 9 * 5 + 4 * 6;

    controller->generic.type = CTRL_PLAYER;
    cr_assert_eq(controller->generic.requests->len, 0);
    controller_handle_buffer(controller, buffer, size);
    cr_assert_eq(controller->generic.requests->len, CTRL_PLAYER_MAX_REQ);

    controller_free(controller);
}

Test(controller_tests, controller_read_with_no_controller)
{
    cr_assert_eq(controller_read(NULL), CTRL_DISCONNECTED);
}

Test(controller_tests, controller_read_simple_complete_request)
{
    int fds[2];
    controller_t *controller = NULL;
    request_t *req = NULL;

    // Arrange
    pipe(fds);
    write(fds[1], "complete request 1\n", 19);
    close(fds[1]);
    controller = controller_new(fds[0]);

    // Act
    cr_assert_eq(controller_read(controller), CTRL_CONNECTED);
    cr_assert_eq(controller->generic.requests->len, 1);
    req = controller_get_last_request(controller);
    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_READY);
    cr_assert_eq(req->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(req->content_size, 18);
    cr_assert_eq(memcmp(req->buffer, "complete request 1", 18), 0);
    cr_assert_eq(controller_read(controller), CTRL_DISCONNECTED);

    // Cleanup
    close(fds[0]);
    controller_free(controller);
}

Test(controller_tests, controller_read_simple_pending_request)
{
    int fds[2];
    controller_t *controller = NULL;
    request_t *req = NULL;

    // Arrange
    pipe(fds);
    write(fds[1], "pending request 1", 17);
    close(fds[1]);
    controller = controller_new(fds[0]);

    // Act
    cr_assert_eq(controller_read(controller), CTRL_CONNECTED);
    cr_assert_eq(controller->generic.requests->len, 1);
    req = controller_get_last_request(controller);
    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_PENDING);
    cr_assert_eq(req->buffer_size, REQ_BUFF_SIZE);
    cr_assert_eq(req->content_size, 17);
    cr_assert_eq(memcmp(req->buffer, "pending request 1", 17), 0);
    cr_assert_eq(controller_read(controller), CTRL_DISCONNECTED);

    // Cleanup
    close(fds[0]);
    controller_free(controller);
}

Test(controller_tests, controller_read_reach_max_requests, .init = cr_redirect_stdout)
{
    int fds[2];
    char buffer[REQ_BUFF_SIZE] = "req1\nreq2\nreq3\nreq4\nreq5\nreq6\nreq7\nreq8\nreq9\nreq10\nreq11\nreq12\nreq13\n";
    size_t size = 9 * 5 + 4 * 6;
    controller_t *controller = NULL;
    request_t *req = NULL;

    // Arrange
    pipe(fds);

    controller = controller_new(fds[0]);
    write(fds[1], buffer, size);
    close(fds[1]);
    controller->generic.type = CTRL_PLAYER;

    // Act
    cr_assert_eq(controller_read(controller), CTRL_CONNECTED);
    cr_assert_eq(controller->generic.requests->len, CTRL_PLAYER_MAX_REQ);
    cr_assert_eq(controller_read(controller), CTRL_DISCONNECTED);

    // Cleanup
    close(fds[0]);
    controller_free(controller);
}

Test(controller_tests, controller_read_with_read_fail, .init = cr_redirect_stderr)
{
    controller_t *controller = controller_new(0);
    controller_state_t status;

    clcc_enable_control(read);
    clcc_return_value_after(read, -1, 0);
    status = controller_read(controller);
    clcc_disable_control(read);

    cr_assert_eq(status, CTRL_CONNECTED);

    controller_free(controller);
}

Test(controller_tests, emit_test_in_1_try, .init = redirect_all_std)
{
    // Arrange
    int fds[2];
    char buffer[1024] = { 0 };
    ssize_t buff_size_content = 0;
    controller_t *controller = NULL;
    server_t *server = server_new();

    pipe(fds);
    fcntl(fds[0], F_SETFL, O_NONBLOCK);
    clcc_return_now(accept, fds[1]);
    controller = server_accept_connection(server);
    clcc_disable_control(accept);

    fd_states_set(&server->fd_actual, fds[1], FD_STATES_W);
    buffer_clear(controller->generic.emissions);
    controller_add_emission(controller, "test\n");

    // Pre-assert
    cr_assert(controller->generic.emissions->bytes == 5);

    // Act
    controller_emit(controller);

    // Assert
    buff_size_content = read(fds[0], buffer, 1024);
    cr_assert_eq(controller->generic.emissions->bytes, 0);
    cr_assert(buff_size_content == 5);
    cr_assert_str_eq(buffer, "test\n");

    // Cleanup
    controller_free(controller);
}

Test(controller_tests, emit_test_in_2_tries, .init = redirect_all_std)
{
    server_t *server = server_new();
    controller_t *controller = NULL;

    clcc_return_now(accept, 4);
    controller = server_accept_connection(server);
    clcc_disable_control(accept);
    fd_states_set(&server->fd_actual, 4, FD_STATES_W);
    buffer_clear(controller->generic.emissions);

    controller_add_emission(controller, "test\n");

    cr_assert(controller->generic.emissions->bytes == 5);

    clcc_return_now(write, 2);
    controller_emit(controller);
    clcc_disable_control(write);
    cr_assert_eq(controller->generic.emissions->bytes, 3);
    clcc_enable_control(write);
    clcc_return_now(write, 2);
    controller_emit(controller);
    clcc_disable_control(write);
    cr_assert_eq(controller->generic.emissions->bytes, 1);
    controller_emit(controller);
    cr_assert_eq(controller->generic.emissions->bytes, 0);
    controller_free(controller);
}

Test(controller_tests, null_controller_emit, .init = redirect_all_std)
{
    controller_emit(NULL);
}

Test(controller_tests, write_fail, .init = redirect_all_std)
{
    server_t *server = server_new();
    controller_t *controller = NULL;

    clcc_return_now(accept, 4);
    controller = server_accept_connection(server);
    clcc_disable_control(accept);
    fd_states_set(&server->fd_actual, 4, FD_STATES_W);
    buffer_clear(controller->generic.emissions);

    cr_assert_eq(controller_add_emission(controller, "test"), true);
    cr_assert_eq(controller->generic.emissions->bytes, 4);

    clcc_return_now(write, -1);
    controller_emit(controller);
    clcc_disable_control(write);
    cr_assert_eq(controller->generic.emissions->bytes, 4);

    clcc_return_now(write, 4);
    controller_emit(controller);
    clcc_disable_control(write);
    cr_assert_eq(controller->generic.emissions->bytes, 0, "bytes: %ld", controller->generic.emissions->bytes);

    controller_free(controller);
}

Test(controller_emissions_tests, add_emission_to_controller, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);

    cr_assert_eq(controller->generic.emissions->bytes, 0);
    controller_add_emission(controller, "Hello World");
    cr_assert_eq(controller->generic.emissions->bytes, 11);
}

Test(controller_emissions_tests, add_emission_with_null_controller, .init = redirect_all_std)
{
    cr_assert_eq(controller_add_emission(NULL, "Hello World"), false);
}

Test(controller_conversion_tests, controller_player_from_generic)
{
    controller_t *controller = controller_new(0);
    player_t *player = player_new(1);

    cr_assert_eq(controller_player_from_generic(controller, player), true);
    cr_assert_eq(controller->player.type, CTRL_PLAYER);
    cr_assert_eq(controller->player.cooldown, 0);
    cr_assert_eq(controller->player.player, player);
}

Test(controller_conversion_tests, null_controller)
{
    vector2u_t position = { 0 };
    player_t *player = player_new(1);

    cr_assert_eq(controller_player_from_generic(NULL, player), false);
}

Test(controller_conversion_tests, null_player)
{
    controller_t *controller = controller_new(0);

    cr_assert_eq(controller_player_from_generic(controller, NULL), false);
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
    cr_assert(controller_has_content_to_read(controller));
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
    cr_assert_not(controller_has_content_to_read(controller));
    server_free(server);
}
