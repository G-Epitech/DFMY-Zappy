/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#pragma once

#include <string>
#include <Ogre.h>

struct Position {
    int x;
    int y;
};

struct Items {
    int food = 0;
    int linemate = 0;
    int deraumere = 0;
    int sibur = 0;
    int mendiane = 0;
    int phiras = 0;
    int thystame = 0;
};

struct Player {
    int id;
    Position position;
    Items inventory;
    int level;
    int orientation;
    std::string team;
    Ogre::SceneNode *node;
};
