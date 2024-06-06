/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** main.c
*/

#include <stdlib.h>
#include "options/options.h"

int main(int ac, char **av)
{
    options_t *options = options_parse(ac, av);

    if (options == NULL)
        return 84;
    options_destroy(options);
    return 0;
}
