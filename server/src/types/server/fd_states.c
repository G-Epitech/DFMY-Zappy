/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** init.c
*/

#include "types/server.h"

static void fd_states_compute_new_max(fd_states_t *states, int old_max)
{
    int new_max = old_max - 1;

    while (new_max >= 0) {
        if (FD_ISSET(new_max, &states->readable) ||
            FD_ISSET(new_max, &states->writable) ||
            FD_ISSET(new_max, &states->except)
        ) {
            break;
        }
        new_max -= 1;
    }
    states->max = new_max;
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
    if (fd < 0)
        return;
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
    if (fd < 0)
        return;
    if (flags & FD_STATES_R)
        FD_CLR(fd, &states->readable);
    if (flags & FD_STATES_W)
        FD_CLR(fd, &states->writable);
    if (flags & FD_STATES_E)
        FD_CLR(fd, &states->except);
    if (fd == states->max)
        fd_states_compute_new_max(states, fd);
}

void fd_states_clear(fd_states_t *states, int flags)
{
    if (flags & FD_STATES_R)
        FD_ZERO(&states->readable);
    if (flags & FD_STATES_W)
        FD_ZERO(&states->writable);
    if (flags & FD_STATES_E)
        FD_ZERO(&states->except);
    fd_states_compute_new_max(states, states->max + 1);
}
