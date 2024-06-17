/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Map
*/

#pragma once

#include <vector>
#include <Ogre.h>
#include "Player.hpp"

struct Tile {
    Items items;
    Ogre::SceneNode *node = nullptr;
};

struct Map {
    std::vector<std::vector<Tile>> tiles = {};
    std::vector<Player> players = {};
    int width = 0;
    int height = 0;
    int timeUnit = 0;
    std::vector<std::string> teams = {};
};
