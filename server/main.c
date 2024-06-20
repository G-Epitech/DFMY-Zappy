/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** main.c
*/

#include "types/trantor/map.h"
#include "types/trantor/player.h"
#include "app.h"

int main(int argc, char **argv)
{
    map_t *map = map_new((vector2u_t){10, 10});
    player_t *player = player_new(NULL);

    if (map == NULL)
        return 84;
    player->position = (vector2u_t){5, 5};
    map->cells[5][5].resources[RES_FOOD] = 1;
    map->cells[6][4].resources[RES_FOOD] = 2;
    map->cells[6][5].resources[RES_FOOD] = 1;
    map->cells[6][6].resources[RES_FOOD] = 3;
    map->cells[7][5].players->len = 1;
    player->level = 3;
    player->direction = DIR_NORTH;
    player_look(player, map);
    map_free(map);
    player_free(player);
    return 0;
}
