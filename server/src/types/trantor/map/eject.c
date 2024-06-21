/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** move.c
*/

#include "types/trantor/map.h"
#include "types/trantor/player.h"

static void update_position_and_notify_players(list_t *players,
    vector2u_t new_pos, direction_t direction)
{
    char *msg = NULL;
    smart_ptr_t *smart_buf = NULL;
    node_t *node = NULL;
    player_t *player = NULL;
    size_t buf_size = 0;

    buf_size = my_asprintf(&msg, "eject: %d", direction);
    if (buf_size > 0)
        smart_buf = smart_ptr_new(msg);
    node = players->first;
    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        player->position = new_pos;
        if (smart_buf) {
            controller_add_emission_from_shared_buffer(
            (controller_t *)player->controller, smart_buf, buf_size,
                EMISSION_COMPLETE);
        }
        node = node->next;
    }
}

bool map_eject_players(map_t *map, player_t *player)
{
    vector2u_t new_pos = player->position;
    map_cell_t *old_cell = NULL;
    map_cell_t *new_cell = NULL;

    map_forward_position(map, &new_pos, player->direction);
    old_cell = MAP_CELL_AT_POS(map, player->position);
    new_cell = MAP_CELL_AT_POS(map, new_pos);
    if (!old_cell || !new_cell)
        return false;
    update_position_and_notify_players(old_cell->players, new_pos,
        player->direction);
    list_merge(new_cell->players, old_cell->players);
    return true;
}
