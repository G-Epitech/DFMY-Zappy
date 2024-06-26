/*
** EPITECH PROJECT, 2024
** Tile.hpp
** File description:
** Tile class
*/

#pragma once

#include <Ogre.h>
#include <map>

class Tile {
public:
    explicit Tile(Ogre::SceneNode *node);
    ~Tile() = default;

    /**
     * @brief Get the Node object
     * @return Ogre::SceneNode*
     */
    [[nodiscard]] Ogre::SceneNode *getNode() const;

    /**
     * @brief Add an item to the tile
     * @param name The name of the item
     * @param quantity The quantity of the item
     * @param scnMgr The Ogre::SceneManager object
     */
    void addItemEntity(const std::string &name, int quantity, Ogre::SceneManager *scnMgr);

    /**
     * @brief Remove an item from the tile
     * @param name The name of the item
     * @param quantity The quantity of the item
     * @param scnMgr The Ogre::SceneManager object
     */
    void removeItemEntity(const std::string &name, int quantity, Ogre::SceneManager *scnMgr);

    /// Items on the tile
    std::map<std::string, std::vector<Ogre::SceneNode *>> items = {};

private:
    Ogre::SceneNode *_node = nullptr;
};
