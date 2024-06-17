/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#include <iostream>
#include "Commands.hpp"
#include "utils/String.hpp"

std::vector<std::string> stonesNames = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

void Commands::_addItemsToTile(Tile &tile, Ogre::SceneManager *scnMgr, const std::string &itemName, int quantity)
{
    Ogre::SceneNode *node = tile.node;
    if (!node || node->numAttachedObjects() == 0)
        return;
    auto tileSize = node->getAttachedObject(0)->getBoundingBox().getSize();
    Ogre::Vector3 pos = node->getPosition();
    Ogre::Vector3 size = node->getAttachedObject(0)->getBoundingBox().getSize();

    for (int i = 0; i < quantity; i++) {
        Ogre::Entity* cubeEntity = scnMgr->createEntity(itemName + ".mesh");
        Ogre::SceneNode* itemNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        auto itemSize = cubeEntity->getBoundingBox().getSize();
        itemNode->attachObject(cubeEntity);

        float randX = pos.x + static_cast<float>(std::rand()) / RAND_MAX * tileSize.x - tileSize.x / 2.0f;
        float randZ = pos.z + static_cast<float>(std::rand()) / RAND_MAX * tileSize.z - tileSize.z / 2.0f;
        float itemY = itemSize.y / 2.0f * 0.1;

        itemNode->setPosition(randX, itemY, randZ);
        itemNode->setScale(0.1f, 0.1f, 0.1f);
        tile.items[itemName].push_back(itemNode);
    }
}

void Commands::_removeItemsFromTile(Tile &tile, Ogre::SceneManager *scnMgr, const std::string &itemName, int quantity)
{
    for (int i = 0; i < quantity; i++) {
        if (tile.items[itemName].empty())
            return;
        Ogre::SceneNode *node = tile.items[itemName].back();
        tile.items[itemName].pop_back();
        scnMgr->destroySceneNode(node);
    }
}

void Commands::map_size(std::string &command, Map &map, Ogre::SceneManager *scnMgr)
{
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 2)
        return;
    map.width = std::stoi(args[0]);
    map.height = std::stoi(args[1]);
    int posx = map.width / 2;
    int posy = map.height / 2;
    for (int i = 0; i < map.width; i++) {
        std::vector<Tile> row;
        posy = map.height / 2;
        for (int j = 0; j < map.height; j++) {
            Ogre::Entity *cubeEntity = scnMgr->createEntity("Cube.mesh");
            Ogre::SceneNode *node = scnMgr->getRootSceneNode()->createChildSceneNode();
            node->attachObject(cubeEntity);

            Ogre::AxisAlignedBox aab = cubeEntity->getBoundingBox();
            Ogre::Vector3 size = aab.getSize();
            node->setPosition(posx * size.x, -size.y / 2.0, posy * size.z);

            Tile tile;

            for (int i = 0; i < stonesNames.size(); i++) {
                tile.items[stonesNames[i]] = {};
            }
            tile.node = node;
            row.push_back(tile);
            posy = posy - 1;
        }
        map.tiles.push_back(row);
        posx = posx - 1;
    }
}

void Commands::tile_content(std::string &command, Map &map, Ogre::SceneManager *scnMgr)
{
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 9)
        return;
    int x = std::stoi(args[0]);
    int y = std::stoi(args[1]);
    if (x < 0 || x >= map.width || y < 0 || y >= map.height)
        return;
    int food = std::stoi(args[2]) - map.tiles[x][y].items["food"].size();
    std::vector<int> stones;
    for (int i = 0; i < stonesNames.size(); i++) {
        stones.push_back(std::stoi(args[3 + i]) - map.tiles[x][y].items[stonesNames[i]].size());
    }

    if (food > 0)
        _addItemsToTile(map.tiles[x][y], scnMgr, "food", food);
    else if (food < 0)
        _removeItemsFromTile(map.tiles[x][y], scnMgr, "food", -food);
    for (int i = 0; i < stonesNames.size(); i++) {
        if (stones[i] > 0)
            _addItemsToTile(map.tiles[x][y], scnMgr, stonesNames[i], stones[i]);
        else if (stones[i] < 0)
            _removeItemsFromTile(map.tiles[x][y], scnMgr, stonesNames[i], -stones[i]);
    }
}
