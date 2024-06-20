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
    player->level = 3;
    player->direction = DIR_NORTH;
    player_look(player, map);
}
