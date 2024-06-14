/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** read.c
*/

#include <unistd.h>
#include <memory.h>
#include <stdio.h>
#include "types/controller.h"
#include "log.h"

bool controller_read_next_token(char *start, size_t size,
    request_token_t *token)
{
    char *end = memchr(start, '\n', size);

    token->content = start;
    if (end) {
        token->size = end - start + 1;
        return token->size == size;
    } else {
        token->size = size;
        return true;
    }
}

void controller_handle_buffer_token(controller_t *controller,
    request_token_t *token)
{
    request_t *req = controller_get_next_pending_request(controller);
    size_t real_size = token->size;

    if (!req)
        return;
    if (token->content[token->size - 1] == '\n') {
        real_size -= 1;
        req->status = REQ_READY;
    } else {
        req->status = REQ_PENDING;
    }
    if (!request_append(req, token->content, real_size)) {
        return log_error("Failed to append token to request buffer of "
            "controller %d. Ignored.", controller->generic.socket);
    }
}

void controller_handle_buffer(controller_t *controller,
    char buffer[REQ_BUFF_SIZE], size_t size)
{
    request_token_t token = { 0 };
    char *start = buffer;
    bool last = false;

    while (!last) {
        last = controller_read_next_token(start, size, &token);
        controller_handle_buffer_token(controller, &token);
        start += token.size;
        size -= token.size;
    }
}

controller_state_t controller_read(controller_t *controller)
{
    char buffer[REQ_BUFF_SIZE] = { 0 };
    generic_controller_t *generic = controller ? &controller->generic : NULL;
    ssize_t read_size = generic ? read(generic->socket, buffer,
        REQ_BUFF_SIZE) : -1;

    if (read_size == 0 || !generic)
        return CTRL_DISCONNECTED;
    if (read_size < 0)
        log_error("Failed to read from socket %d", generic->socket);
    else
        controller_handle_buffer(controller, buffer, read_size);
    return CTRL_CONNECTED;
}
