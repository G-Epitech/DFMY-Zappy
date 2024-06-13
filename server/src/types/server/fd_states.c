/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** init.c
*/

#include "types/server.h"

static void fd_states_compute_new_max(fd_states_t *states)
{
    int max = -1;

    for (int i = states->max; i >= 0; i--) {
        if (FD_ISSET(i, &states->readable) ||
            FD_ISSET(i, &states->writable) ||
            FD_ISSET(i, &states->except)
        ) {
            max = i;
            break;
        }
    }
    states->max = max;
}

void fd_states_init(fd_states_t *states)
{
    FD_ZERO(&states->readable);
    FD_ZERO(&states->writable);
    FD_ZERO(&states->except);
    states->max = -1;
}

void fd_states_set(fd_states_t *states, int fd, int flags)
{
    if (flags & FD_STATES_R)
        FD_SET(fd, &states->readable);
    if (flags & FD_STATES_W)
        FD_SET(fd, &states->writable);
    if (flags & FD_STATES_E)
        FD_SET(fd, &states->except);
    if (fd > states->max)
        states->max = fd;
}

void fd_states_unset(fd_states_t *states, int fd, int flags)
{
    if (flags & FD_STATES_R)
        FD_CLR(fd, &states->readable);
    if (flags & FD_STATES_W)
        FD_CLR(fd, &states->writable);
    if (flags & FD_STATES_E)
        FD_CLR(fd, &states->except);
    fd_states_compute_new_max(states);
}

void fd_states_clear(fd_states_t *states, int flags)
{
    if (flags & FD_STATES_R)
        FD_ZERO(&states->readable);
    if (flags & FD_STATES_W)
        FD_ZERO(&states->writable);
    if (flags & FD_STATES_E)
        FD_ZERO(&states->except);
    fd_states_compute_new_max(states);
}
