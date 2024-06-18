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

    if ((int)(player->inventory[resource] + quantity) < 0)
        return false;
    if (resource == RES_FOOD) {
        lives += (float)quantity * PLAYER_LIFE_UNITS_PER_FOOD;
        if (lives < 0)
            return false;
        if (lives == 0) {
            player->inventory[RES_FOOD] = 0;
            return true;
        }
        player_update_lives(player, lives);
    } else {
        player->inventory[resource] += quantity;
    }
    return true;
}
