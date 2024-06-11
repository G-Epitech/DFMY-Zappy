/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** stop.c
*/

#include "app.h"

bool *app_stopped(void)
{
    static bool stopped = false;

    return &stopped;
}

void app_stop(void)
{
    *app_stopped() = true;
}
