/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Egg
*/

#pragma once

#include <Ogre.h>
#include "Utils.hpp"

struct Egg {
    int id;
    Position position;
    Ogre::SceneNode *node;
};
