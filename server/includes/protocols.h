/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** graphic.h
*/

#pragma once

// Length of the command in the graphic protocol
#define GRAPHIC_PROTOCOL_CMD_LEN 3

// @brief Structure representing a protocol request handler
typedef struct protocol_request_handler_s {
    // @brief The command name of the request
    const char *command;
    // @brief The handler function
    void (*function)(app_t *app, controller_t *controller, request_t *request);
} protocol_request_handler_t;
