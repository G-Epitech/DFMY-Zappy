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
#include "Teams.hpp"
#include "constants/Player.hpp"

class Player {
public:
    Player(int id, std::string team);
    ~Player() = default;

    /**
     * @brief Get the team of the player
     * @return The team of the player
     */
    [[nodiscard]] std::string getTeam() const;

    /**
     * @brief Get the id of the player
     * @return The id of the player
     */
    int getId() const;

    /**
     * @brief Create the entity of the player
     * @param scnMgr Scene manager of the GUI
     * @param teams List of teams
     * @param tileNode Node of the tile
     */
    void createEntity(Ogre::SceneManager *scnMgr, Teams &teams, Ogre::Node *tileNode);

    /**
     * @brief Update the size of the entity of the player
     * This function is usefully to see the player grow when he levels up
     * @param tileNode Node of the tile
     */
    void updateEntitySize(Ogre::Node *tileNode) const;

    /**
     * @brief Add an item to the inventory of the player
     * @param item Item to add
     * @param quantity Quantity of the item
     */
    void addInventoryItem(const std::string &item, int quantity);

    /**
     * @brief Remove an item from the inventory of the player
     * @param item Item to remove
     * @return Quantity of the item removed
     */
    void removeInventoryItem(const std::string &item, int quantity);

    /**
     * @brief Get the quantity of an item in the inventory of the player
     * @param item Item to get the quantity of
     * @return Quantity of the item
     */
    [[nodiscard]] int getItemQuantity(const std::string &item) const;

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
