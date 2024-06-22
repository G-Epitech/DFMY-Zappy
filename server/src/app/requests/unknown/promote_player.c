/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** promote_graphic.c
*/

#include <string.h>
#include "app.h"
#include "types/trantor/egg.h"
#include "types/trantor/player.h"

static team_t *get_team_by_name(world_t *world, char *name, size_t len)
{
    node_t *node = world->teams->first;
    team_t *team = NULL;

    while (node) {
        team = NODE_TO_PTR(node, team_t *);
        if (strlen(team->name) == len && memcmp(team->name, name, len) == 0)
            return team;
        node = node->next;
    }
    return NULL;
}

static void send_player_info(controller_t *controller, player_t *player)
{
    controller_add_emission(controller,
        "%zu\n%zu %zu\n",
        player->team->eggs->len,
        player->position.x,
        player->position.y
    );
}

static void notify_graphics_of_new_player(server_t *server, player_t *p,
    egg_t *e)
{
    size_t *ivt = p->inventory;
    vector2u_t *p_pos = &p->position;
    bool success = controllers_add_emission(server->controllers, CTRL_GRAPHIC,
        "pnw %zu %zu %zu %u %zu %s\n"
        "pin %zu %zu %zu %zu %zu %zu %zu %zu %zu %zu\n"
        "ebo %zu\n",
        p->id, p_pos->x, p_pos->y, p->direction, p->level, p->team->name,
        p->id, p_pos->x, p_pos->y, ivt[RES_FOOD], ivt[RES_LINEMATE],
        ivt[RES_DERAUMERE], ivt[RES_SIBUR], ivt[RES_MENDIANE],
        ivt[RES_PHIRAS], ivt[RES_THYSTAME], e->id
    );

    if (!success)
        return log_error("Failed to format new player emission");
}

void app_try_promote_controller_to_player(app_t *app,
    controller_t *controller, request_t *request, size_t team_name_len)
{
    team_t *team = get_team_by_name(app->world, request->buffer,
        team_name_len);
    egg_t *egg = team ? team_get_random_egg(team) : NULL;
    player_t *player = egg ? world_hatch_egg(app->world, egg) : NULL;

    if (!team || !egg || !player) {
        controller_add_emission(controller, "ko\n");
        return;
    }
    controller_player_from_generic(controller, player);
    notify_graphics_of_new_player(app->server, player, egg);
    world_kill_egg(app->world, egg);
    send_player_info(controller, player);
}
