/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#pragma once

#include <string>
#include <Ogre.h>
#include "Utils.hpp"

class Player {
public:
    Player(int id, std::string team);
    ~Player() = default;

    /**
     * @brief Get the team of the player
     * @return The team of the player
     */
    std::string getTeam() const;

    /**
     * @brief Get the id of the player
     * @return The id of the player
     */
    int getId() const;

    /// Position of the player in the map
    Position position;

    /// Level of the player
    int level;

    /// Orientation of the player
    int orientation;

    /// Node of the player
    Ogre::SceneNode *node;

private:
    /// Team of the player
    std::string _team;

    /// Id of the player
    int _id;

    /// Inventory of the player
    std::map<std::string, int> _inventory;
};
