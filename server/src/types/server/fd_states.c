/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** init.c
*/

#include "types/server.h"

void fd_states_init(fd_states_t *states)
{
    FD_ZERO(&states->readable);
    FD_ZERO(&states->writable);
    FD_ZERO(&states->except);
    states->max = 0;
}
