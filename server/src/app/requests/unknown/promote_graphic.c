/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** promote_graphic.c
*/

#include "app.h"
#include "types/trantor/egg.h"

static void send_laid_eggs_info(controller_t *controller, world_t *world)
{
    node_t *node_team = world->teams->first;
    node_t *node_egg = NULL;
    team_t *team = NULL;
    egg_t *egg = NULL;

    while (node_team) {
        team = NODE_TO_PTR(node_team, team_t *);
        node_egg = team->eggs->first;
        while (node_egg) {
            egg = NODE_TO_PTR(node_egg, egg_t *);
            controller_add_emission(controller, "enw %zu %ld %zu %zu\n",
                egg->id, egg->laid_by, egg->position.x, egg->position.y
            );
            node_egg = node_egg->next;
        }
        node_team = node_team->next;
    }
}

static void send_players_info(controller_t *controller, world_t *world)
{
    node_t *node = world->players->first;
    player_t *player = NULL;

    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        controller_add_emission(controller,
            "pnw %zu %zu %zu %u %zu %s\n",
            player->id, player->position.x, player->position.y,
            player->direction, player->level, player->team->name
        );
        node = node->next;
    }
}

static void send_incantation_infos(controller_t *controller,
    incantation_t *incantation)
{
    node_t *node = incantation->players->first;
    player_t *player = NULL;
    player_t *requester = incantation->requester;

    controller_add_emission(controller, "pic %zu %zu %u",
        incantation->location.x, incantation->location.y,
        incantation->level
    );
    if (requester)
        controller_add_emission(controller, " %zu", requester->id);
    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        if (player != requester)
            controller_add_emission(controller, " %zu", player->id);
        node = node->next;
    }
    controller_add_emission(controller, "\n");
}

static void send_current_incantations(controller_t *controller, world_t *world)
{
    node_t *node = world->incantations->first;
    incantation_t *incantation = NULL;

    while (node) {
        incantation = NODE_TO_PTR(node, incantation_t *);
        send_incantation_infos(controller, incantation);
        node = node->next;
    }
}

static void send_map_size(controller_t *controller,
    world_t *world)
{
    controller_add_emission(controller, "msz %zu %zu\n", world->map->size.x,
        world->map->size.y);
}

void app_try_promote_controller_to_graphic(app_t *app,
    controller_t *controller)
{
    bool promoted = controller_graphic_from_generic(controller,
        app->world->map);

    if (!promoted) {
        log_error("Controller on socket %d could not be promoted to graphic."
            " Disconnecting.", controller->generic.socket);
        return server_disconnect_controller(app->server, controller);
    }
    log_info("Controller on socket %d has been promoted to graphic."
            " Emissions buffer smartly resized to %zu bytes.",
            controller->generic.socket, controller->graphic.emissions->size);
    send_map_size(controller, app->world);
    send_laid_eggs_info(controller, app->world);
    send_players_info(controller, app->world);
    send_current_incantations(controller, app->world);
}
