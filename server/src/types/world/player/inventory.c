/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** inventory.c
*/

#include "types/world/player.h"

bool player_set_inventory_resource(player_t *player, resource_t resource,
    int quantity)
{
    time_unit_t t_units = 0;

    if (resource == RES_FOOD) {
        t_units = player->lives + (float)quantity * PLAYER_LIFE_UNITS_PER_FOOD;
        if (t_units < 0)
            return false;
        player_update_lives(player, t_units);
    } else {
        player->inventory[resource] += quantity;
        if (player->inventory[resource] < 0)
            player->inventory[resource] = 0;
    }
    return true;
}
