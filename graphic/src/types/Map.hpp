/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Map
*/

#pragma once

#include <vector>
#include <Ogre.h>
#include "Egg.hpp"
#include "Player.hpp"
#include "constants/Broadcast.hpp"

struct Tile {
    std::map<std::string, std::vector<Ogre::SceneNode *>> items = {};
    Ogre::SceneNode *node = nullptr;
};

struct Circle {
    Ogre::ManualObject *circle = nullptr;
    Ogre::SceneNode *node = nullptr;
    float radius = BROADCAST_CIRCLE_RADIUS;
};

struct Map {
    std::vector<std::vector<Tile>> tiles = {};
    std::vector<Player> players = {};
    int width = 0;
    int height = 0;
    int timeUnit = 0;
    std::vector<std::string> teams = {};
    std::vector<Egg> eggs = {};
    std::vector<Circle> broadcastCircles = {};
};

bool operator==(const Circle &lhs, const Circle &rhs);
