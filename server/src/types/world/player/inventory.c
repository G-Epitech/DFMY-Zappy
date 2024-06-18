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
    time_unit_t lives = player->lives;

    if (resource == RES_FOOD) {
        lives += (float)quantity * PLAYER_LIFE_UNITS_PER_FOOD;
        if (lives < 0)
            return false;
        player_update_lives(player, lives);
    } else {
        player->inventory[resource] += quantity;
    }
    return true;
}
