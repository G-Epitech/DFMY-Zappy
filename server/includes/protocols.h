/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** graphic.h
*/

#pragma once

// Length of the command in the graphic protocol
#define GRAPHIC_PROTOCOL_CMD_LEN 3

// Max length of a command in the graphic protocol
#define PLAYER_PROTOCOL_MAX_CMD_LEN 11

// @brief Structure representing a protocol request handler
typedef struct gui_request_handler_s {
    // @brief The command name of the request
    const char *command;
    // @brief The handler function
    void (*function)(app_t *app, controller_t *controller, request_t *request);
} gui_request_handler_t;

// @brief Structure representing a protocol request handler
typedef struct player_request_handler_s {
    // @brief The command name of the request
    const char *command;
    // @brief Command cooldown
    const time_unit_t cooldown;
    // @brief The handler function called when the request is ready
    bool (*onstart)(app_t *app, player_controller_t *controller,
        request_t *request);
    // @brief The handler function called when the request is finished
    void (*onfinish)(app_t *app, player_controller_t *controller,
        request_t *request);
} player_request_handler_t;
