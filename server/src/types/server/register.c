/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** register.c
*/

#include "types/server.h"
#include "types/world/player.h"

void server_player_register(server_t *server, player_t *player)
{
    player->number = server->current_player_number;
    server->current_player_number += 1;
}
