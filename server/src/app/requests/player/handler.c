/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** handler.c
*/

#include <string.h>
#include "app.h"
#include "protocols.h"

static const player_request_handler_t handlers[] = {
    { "Forward", 7,
        &app_handle_player_request_forward_onstart,
        &app_handle_player_request_forward_onfinish
    },
    { "Right", 7,
        &app_handle_player_request_turn_right_onstart,
        &app_handle_player_request_turn_right_onfinish
    },
    { "Left", 7,
        &app_handle_player_request_turn_left_onstart,
        &app_handle_player_request_turn_left_onfinish
    },
    { "Look", 7,
        &app_handle_player_request_look_onstart,
        &app_handle_player_request_look_onfinish
    },
    { "Inventory", 1,
        &app_handle_player_request_inventory_onstart,
        &app_handle_player_request_inventory_onfinish
    },
    { "Broadcast", 7,
        &app_handle_player_request_broadcast_onstart,
        &app_handle_player_request_broadcast_onfinish
    },
    { "Connect_nbr", 0,
        &app_handle_player_request_connect_nbr_onstart,
        &app_handle_player_request_connect_nbr_onfinish
    },
    { "Fork", 42,
        &app_handle_player_request_fork_onstart,
        &app_handle_player_request_fork_onfinish
    },
    { "Eject", 7,
        &app_handle_player_request_eject_onstart,
        &app_handle_player_request_eject_onfinish
    },
    { "Take", 7,
        &app_handle_player_request_take_onstart,
        &app_handle_player_request_take_onfinish
    },
    { "Set", 7,
        &app_handle_player_request_set_onstart,
        &app_handle_player_request_set_onfinish
    },
    { "Incantation", 300,
        &app_handle_player_request_incantation_onstart,
        NULL
    }
};

static const size_t handlers_size =
sizeof(handlers) / sizeof(player_request_handler_t);

static player_request_handler_t *find_handler(const char *name)
{
    for (size_t i = 0; i < handlers_size; i++) {
        if (strcmp(handlers[i].command, name) == 0)
            return (player_request_handler_t *) &handlers[i];
    }
    return NULL;
}

static void set_cooldown_or_exec(app_t *app, controller_t *controller,
    request_t *request, player_request_handler_t *handler)
{
    player_controller_t *player_controller = &controller->player;

    if (handler->onstart &&
        !(handler->onstart(app, player_controller, request))
    ) {
        controller_add_emission(controller, "ko\n");
        request->status = REQ_FINISHED;
        return;
    }
    player_controller->cooldown = handler->cooldown;
    request->status = REQ_HANDLING;
    if (handler->cooldown == 0) {
        if (handler->onfinish)
            handler->onfinish(app, player_controller, request);
        request->status = REQ_FINISHED;
    } else {
        world_register_event(app->world, player_controller->cooldown);
    }
}

static void app_handle_player_request_start(app_t *app,
    controller_t *controller, request_t *request)
{
    request_token_t token = { 0 };
    player_request_handler_t *handler = NULL;
    char cmd[PLAYER_PROTOCOL_MAX_CMD_LEN + 1] = { 0 };

    request_get_token(request, 0, &token);
    if (token.size <= PLAYER_PROTOCOL_MAX_CMD_LEN) {
        memcpy(cmd, token.content, token.size);
        handler = find_handler(cmd);
    }
    if (!handler) {
        request->status = REQ_FINISHED;
        controller_add_emission(controller, "ko\n");
        return;
    }
    set_cooldown_or_exec(app, controller, request, handler);
}

static void app_handle_player_request_end(app_t *app, controller_t *controller,
    request_t *request)
{
    request_token_t token = { 0 };
    player_request_handler_t *handler = NULL;
    player_controller_t *player_controller = &controller->player;
    char cmd[PLAYER_PROTOCOL_MAX_CMD_LEN + 1] = { 0 };

    request_get_token(request, 0, &token);
    if (token.size <= PLAYER_PROTOCOL_MAX_CMD_LEN) {
        memcpy(cmd, token.content, token.size);
        handler = find_handler(cmd);
    }
    if (handler && handler->onfinish)
        handler->onfinish(app, player_controller, request);
    request->status = REQ_FINISHED;
}

void app_handle_player_request(app_t *app, controller_t *controller,
    request_t *request)
{
    player_controller_t *player_controller = &controller->player;

    if (player_controller->player->incantation ||
        player_controller->cooldown > 0
    ) {
        return;
    }
    if (request->status == REQ_READY)
        app_handle_player_request_start(app, controller, request);
    else
        app_handle_player_request_end(app, controller, request);
}
