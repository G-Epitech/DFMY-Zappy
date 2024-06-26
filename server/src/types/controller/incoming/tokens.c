/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** player.c
*/

#include <string.h>
#include "types/controller.h"

bool controller_read_next_incoming_token(controller_t *controller,
    incoming_token_t *token)
{
    buffer_t *incoming = controller->generic.incoming;
    size_t size = buffer_read_delim(incoming, '\n');

    token->content = incoming->data;
    token->size = size;
    if (token->size)
        token->complete = token->content[token->size - 1] == '\n';
    return size == incoming->bytes;
}

void controller_consume_incoming_token(controller_t *controller,
    incoming_token_t *token)
{
    buffer_clear_size(controller->generic.incoming, token->size);
    token->consumed = true;
}
