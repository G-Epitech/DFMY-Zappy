/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** init.c
*/

#include <unistd.h>
#include "types/buffer.h"
#include "types/controller.h"
#include "types/trantor/player.h"

bool controller_player_from_generic(controller_t *controller,
    player_t *player)
{
    if (!controller || !player)
        return false;
    controller->player.type = CTRL_PLAYER;
    controller->player.cooldown = 0;
    controller->player.player = player;
    player->controller = (player_controller_t *) controller;
    return true;
}

bool controller_graphic_from_generic(controller_t *controller, map_t *map)
{
    buffer_t **buffer = NULL;
    size_t buff_size = CTRL_GRAPHIC_AVERAGE_EMISSION_SIZE;
    const size_t page_size = getpagesize();

    if (!controller || !map)
        return false;
    buff_size *= map->size.x * map->size.y;
    buff_size = MAX(buff_size, CTRL_EMIT_BUFF_SIZE);
    buff_size = buff_size % page_size != 0
        ? buff_size + page_size - (buff_size % page_size)
        : buff_size;
    controller->graphic.type = CTRL_GRAPHIC;
    buffer = &controller->graphic.emissions;
    if ((*buffer)->size < buff_size)
        *buffer = buffer_resize(*buffer, buff_size);
    return (*buffer != NULL);
}
