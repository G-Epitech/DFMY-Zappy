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
#include "types/list.h"
#include "types/controller.h"
#include "types/emission.h"
#include "types/trantor/player.h"

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
    clcc_enable_control(malloc);
    clcc_return_value_after(malloc, NULL, 1);
    cr_assert_null(controller_new(0));
    clcc_disable_control(malloc);
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
    emission_t *emission = NULL;

    pipe(fds);
    fcntl(fds[1], F_SETFL, O_NONBLOCK);
    controller = controller_new(fds[1]);
    controller_add_emission(controller, strdup("test"), 4, 0);
    emission = NODE_TO_PTR(controller->generic.emissions->first, emission_t *);

    // Pre-assert
    cr_assert(controller->generic.emissions->len == 1);
    cr_assert(emission->written == 0);
    cr_assert(emission->buffer_size == 4);

    // Act
    controller_emit(controller);

    // Assert
    buff_size_content = read(fds[0], buffer, 1024);
    cr_assert_eq(controller->generic.emissions->len, 0);
    cr_assert_eq(emission->written, 4);
    cr_assert(buff_size_content == 5);
    cr_assert_str_eq(buffer, "test\n");

    // Cleanup
    controller_free(controller);
}

Test(controller_tests, emit_test_in_2_tries, .init = redirect_all_std)
{
    controller_t *controller = controller_new(1);
    emission_t *emission = NULL;

    controller_add_emission(controller, strdup("test"), 4, 0);
    emission = NODE_TO_PTR(controller->generic.emissions->first, emission_t *);

    cr_assert(controller->generic.emissions->len == 1);
    cr_assert(emission->written == 0);
    cr_assert(emission->buffer_size == 4);

    clcc_return_now(write, 2);
    controller_emit(controller);
    clcc_disable_control(write);
    cr_assert_eq(controller->generic.emissions->len, 1);
    cr_assert_eq(emission->written, 2);
    clcc_enable_control(write);
    clcc_return_value_after(write, -1, 1);
    controller_emit(controller);
    clcc_disable_control(write);
    cr_assert_eq(controller->generic.emissions->len, 1);
    cr_assert_eq(emission->written, 4);
    controller_emit(controller);
    cr_assert_eq(controller->generic.emissions->len, 0);
    controller_free(controller);
}

Test(controller_tests, emit_test_partial, .init = redirect_all_std)
{
    // Arrange
    // Arrange
    int fds[2];
    char buffer[1024] = { 0 };
    ssize_t buff_size_content = 0;
    controller_t *controller = NULL;
    emission_t *emission = NULL;

    pipe(fds);
    fcntl(fds[1], F_SETFL, O_NONBLOCK);
    controller = controller_new(fds[1]);
    controller_add_emission(controller, strdup("test"), 4, EMISSION_PARTIAL);
    emission = NODE_TO_PTR(controller->generic.emissions->first, emission_t *);

    // Pre-assert
    cr_assert(controller->generic.emissions->len == 1);
    cr_assert(emission->written == 0);
    cr_assert(emission->buffer_size == 4);

    // Act
    controller_emit(controller);

    // Assert
    buff_size_content = read(fds[0], buffer, 1024);
    cr_assert_eq(controller->generic.emissions->len, 0);
    cr_assert_eq(emission->written, 4);
    cr_assert(buff_size_content == 4);
    cr_assert_str_eq(buffer, "test");

    // Cleanup
    controller_free(controller);
}


Test(controller_tests, null_controller_emit, .init = redirect_all_std)
{
    controller_emit(NULL);
}

Test(controller_tests, write_fail, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);
    char *buffer = strdup("test");

    controller_add_emission(controller, buffer, 4, 0);

    clcc_return_now(write, -1);
    controller_emit(controller);
    clcc_disable_control(write);
    cr_assert_eq(controller->generic.emissions->len, 1);

    clcc_return_now(write, 4);
    controller_emit(controller);
    clcc_disable_control(write);
    cr_assert_eq(controller->generic.emissions->len, 0);

    controller_free(controller);
}

Test(controller_tests, controller_write)
{
    controller_t *controller = controller_new(0);

    cr_assert_eq(controller_write(controller, NULL, 4), -1);
    cr_assert_eq(controller_write(NULL, "test", 4), -1);
}

Test(controller_emissions_tests, add_emission_to_controller, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);
    char *buffer = strdup("Hello World");

    cr_assert_eq(controller->generic.emissions->len, 0);
    controller_add_emission(controller, buffer, 11, 0);
    cr_assert_eq(controller->generic.emissions->len, 1);
    list_free(controller->generic.emissions, &emission_free_as_node_data);
}

Test(controller_emissions_tests, add_emission_to_controller_with_calloc_fail, .init = redirect_all_std) {
    controller_t *controller = controller_new(0);
    char *buffer = strdup("Hello World");

    clcc_return_now(calloc, NULL);
    cr_assert_eq(controller_add_emission(controller, buffer, 11, 0), false);
    clcc_disable_control(calloc);
}

Test(controller_emissions_tests, add_emission_to_controller_with_malloc_fail, .init = redirect_all_std) {
    controller_t *controller = controller_new(0);
    char *buffer = strdup("Hello World");
    bool success = false;

    clcc_return_now(malloc, NULL);
    success = controller_add_emission(controller, buffer, 11, 0);
    clcc_disable_control(malloc);
 //   cr_assert_eq(success, false);
}

Test(controller_emissions_tests, add_emission_to_controller_with_calloc_emission_fail, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);
    char *buffer = strdup("Hello World");

    clcc_enable_control(calloc);
    clcc_return_value_after(calloc, NULL, 1);
    cr_assert_eq(controller_add_emission(controller, buffer, 11, 0), false);
    clcc_disable_control(calloc);
}

Test(controller_emissions_tests, add_emission_with_null_controller, .init = redirect_all_std)
{
    char *buffer = strdup("Hello World");
    cr_assert_eq(controller_add_emission(NULL, buffer, 11, 0), false);
}

Test(controller_emissions_tests, add_emission_with_null_smart_ptr, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);
    cr_assert_eq(controller_add_emission(controller, NULL, 11, 0), false);
    controller_free(controller);
}

Test(controller_emissions_tests, add_shared_emissions_with_calloc_fail, .init = redirect_all_std)
{
    list_t *list = list_new();
    controller_t *controller = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);
    emission_params_t params = {
        .buffer = strdup("Hello World"),
        .buffer_size = 11,
        .flags = 0
    };

    controller2->generic.type = CTRL_GRAPHIC;
    controller3->generic.type = CTRL_GRAPHIC;
    controller->generic.type = CTRL_PLAYER;
    list_push(list, NODE_DATA_FROM_PTR(controller));
    list_push(list, NODE_DATA_FROM_PTR(controller2));
    list_push(list, NODE_DATA_FROM_PTR(controller3));
    clcc_return_now(calloc, NULL);
    cr_assert_eq(controllers_add_emission(list, &params, CTRL_UNKNOWN),
                 false);
    cr_assert_eq(controllers_add_emission(list, &params, CTRL_UNKNOWN),
                 false);
    cr_assert_eq(controllers_add_emission(list, &params, CTRL_UNKNOWN),
                 false);
    clcc_disable_control(calloc);
    cr_assert_eq(controller->generic.emissions->len, 0);
    cr_assert_eq(controller2->generic.emissions->len, 0);
    cr_assert_eq(controller3->generic.emissions->len, 0);
    list_free(list, &controller_free_as_node_data);
}

Test(controller_emissions_tests, add_shared_emissions_with_null_list, .init = redirect_all_std)
{
    emission_params_t params = {
        .buffer = strdup("Hello World"),
        .buffer_size = 11,
        .flags = 0
    };

    cr_assert_eq(controllers_add_emission(NULL, &params, CTRL_UNKNOWN), false);
    cr_assert_eq(controllers_add_emission(NULL, &params, 0), false);
    cr_assert_eq(controllers_add_emission(NULL, &params, CTRL_UNKNOWN), false);
    free(params.buffer);
}

Test(controller_emissions_tests, add_shared_emissions_with_null_buffer, .init = redirect_all_std)
{
    list_t *list = list_new();

    cr_assert_eq(controllers_add_emission(list, NULL, CTRL_UNKNOWN), false);
    cr_assert_eq(controllers_add_emission(list, NULL, 0), false);
    cr_assert_eq(controllers_add_emission(list, NULL, CTRL_UNKNOWN), false);
    list_free(list, NULL);
}

Test(controller_emissions_tests, add_all_shared_emissions, .init = redirect_all_std)
{
    list_t *list = list_new();
    controller_t *controller = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);
    emission_params_t params = {
        .buffer = strdup("Hello World"),
        .buffer_size = 11,
        .flags = 0
    };

    controller->generic.type = CTRL_PLAYER;
    controller2->generic.type = CTRL_GRAPHIC;
    controller3->generic.type = CTRL_UNKNOWN;
    list_push(list, NODE_DATA_FROM_PTR(controller));
    list_push(list, NODE_DATA_FROM_PTR(controller2));
    list_push(list, NODE_DATA_FROM_PTR(controller3));
    controllers_add_emission(list, &params, CTRL_GRAPHIC | CTRL_PLAYER);
    cr_assert_eq(controller->generic.emissions->len, 1);
    cr_assert_eq(controller2->generic.emissions->len, 1);
    cr_assert_eq(controller3->generic.emissions->len, 0);
    list_free(list, &controller_free_as_node_data);
}

Test(controller_emissions_tests, add_all_shared_emissions_with_null_buffer, .init = redirect_all_std)
{
    list_t *list = list_new();
    controller_t *controller = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);
    emission_params_t params = {
        .buffer = NULL,
        .buffer_size = 11,
        .flags = 0
    };

    controller->generic.type = CTRL_PLAYER;
    controller2->generic.type = CTRL_GRAPHIC;
    controller3->generic.type = CTRL_UNKNOWN;
    list_push(list, NODE_DATA_FROM_PTR(controller));
    list_push(list, NODE_DATA_FROM_PTR(controller2));
    list_push(list, NODE_DATA_FROM_PTR(controller3));
    controllers_add_emission(list, &params, CTRL_GRAPHIC | CTRL_PLAYER);
    cr_assert_eq(controller->generic.emissions->len, 0);
    cr_assert_eq(controller2->generic.emissions->len, 0);
    cr_assert_eq(controller3->generic.emissions->len, 0);
    list_free(list, &controller_free_as_node_data);
}

Test(controller_emissions_tests, add_graphics_shared_emissions, .init = redirect_all_std)
{
    list_t *list = list_new();
    controller_t *controller = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);
    emission_params_t params = {
        .buffer = strdup("Hello World"),
        .buffer_size = 11,
        .flags = 0
    };

    controller2->generic.type = CTRL_GRAPHIC;
    controller3->generic.type = CTRL_GRAPHIC;
    controller->generic.type = CTRL_PLAYER;
    list_push(list, NODE_DATA_FROM_PTR(controller));
    list_push(list, NODE_DATA_FROM_PTR(controller2));
    list_push(list, NODE_DATA_FROM_PTR(controller3));
    controllers_add_emission(list, &params, CTRL_GRAPHIC);
    cr_assert_eq(controller->generic.emissions->len, 0);
    cr_assert_eq(controller2->generic.emissions->len, 1);
    cr_assert_eq(controller3->generic.emissions->len, 1);
    list_free(list, &controller_free_as_node_data);
}

Test(controller_emissions_tests, end_emission_on_null_controller, .init = redirect_all_std)
{
    cr_assert_eq(controller_end_emission(NULL), false);
}

Test(controller_emissions_tests, end_emission_on_null_emission, .init = redirect_all_std)
{
    controller_t *controller = controller_new(1);

    cr_assert_eq(controller_end_emission(controller), true);
    controller_free(controller);
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
