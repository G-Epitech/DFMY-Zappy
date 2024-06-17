/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#pragma once

#include <string>

struct Position {
    int x;
    int y;
};

struct Items {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
};

struct Player {
    int id;
    Position position;
    Items inventory;
    int level;
    int orientation;
    std::string team;
};