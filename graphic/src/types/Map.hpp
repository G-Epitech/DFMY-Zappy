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
#include "constants/Incantation.hpp"

#define MAP_TILE_Y_OFFSET 0.4f
#define MAP_TILE_X_OFFSET 0.4f

struct Tile {
    std::map<std::string, std::vector<Ogre::SceneNode *>> items = {};
    Ogre::SceneNode *node = nullptr;
};

struct Circle {
    Ogre::ManualObject *circle = nullptr;
    Ogre::SceneNode *node = nullptr;
    float radius = BROADCAST_CIRCLE_RADIUS;
};

struct Sphere {
    Ogre::ManualObject *sphere = nullptr;
    Ogre::SceneNode *node = nullptr;
    float radius = INCANTATION_SPHERE_RADIUS;
    bool isGrowing = true;
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
    std::vector<Sphere> incantationSpheres = {};
};

bool operator==(const Circle &lhs, const Circle &rhs);
bool operator==(const Sphere &lhs, const Sphere &rhs);
