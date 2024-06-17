/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Map
*/

#pragma once

#include <vector>
#include "Player.hpp"

struct Tile {
    Items items;
};

struct Map {
    std::vector<std::vector<Tile>> tiles;
    std::vector<Player> players;
    int width;
    int height;
    int timeUnit;
    std::vector<std::string> teams;
};
