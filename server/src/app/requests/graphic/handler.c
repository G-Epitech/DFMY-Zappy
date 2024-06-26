/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** handler.c
*/

#include <string.h>
#include "app.h"
#include "protocols.h"

static const gui_request_handler_t handlers[] = {
    { "tna", &app_handle_gui_request_teams_names },
    { "msz", &app_handle_gui_request_map_size },
    { "bct", &app_handle_gui_request_map_cell_content },
    { "mct", &app_handle_gui_request_map_content },
    { "ppo", &app_handle_gui_request_player_position },
    { "plv", &app_handle_gui_request_player_level },
    { "pin", &app_handle_gui_request_player_inventory },
    { "sgt", &app_handle_gui_request_get_time_unit },
    { "sst", &app_handle_gui_request_set_time_unit },
};

static const size_t handlers_size =
sizeof(handlers) / sizeof(gui_request_handler_t);

static gui_request_handler_t *find_handler(const char *name)
{
    for (size_t i = 0; i < handlers_size; i++) {
        if (strcmp(handlers[i].command, name) == 0)
            return (gui_request_handler_t *)&handlers[i];
    }
    return NULL;
}

void app_handle_graphic_request(app_t *app, controller_t *controller,
    request_t *request)
{
    incoming_token_t token = { 0 };
    gui_request_handler_t *handler = NULL;
    char cmd[GRAPHIC_PROTOCOL_CMD_LEN + 1] = { 0 };

    request_get_token(request, 0, &token);
    if (token.size == GRAPHIC_PROTOCOL_CMD_LEN) {
        memcpy(cmd, token.content, token.size);
        handler = find_handler(cmd);
    }
    if (!handler)
        controller_add_emission(controller, "suc\n");
    else
        handler->function(app, controller, request);
    request->status = REQ_FINISHED;
}
