/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** main.c
*/

#include "options/options.h"

int main(int ac, char **av)
{
    options_t options = {0};

    if (!options_parse(ac, av, &options))
        return 84;
    return 0;
}
