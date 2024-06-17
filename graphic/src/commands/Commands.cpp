/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#include <iostream>
#include "Commands.hpp"
#include "utils/String.hpp"

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
    int food = std::stoi(args[2]);
    int linemate = std::stoi(args[3]);
    int deraumere = std::stoi(args[4]);
    int sibur = std::stoi(args[5]);
    int mendiane = std::stoi(args[6]);
    int phiras = std::stoi(args[7]);
    int thystame = std::stoi(args[8]);

    Tile &tile = map.tiles[x][y];

    tile.items.food = food;
    tile.items.linemate = linemate;
    tile.items.deraumere = deraumere;
    tile.items.sibur = sibur;
    tile.items.mendiane = mendiane;
    tile.items.phiras = phiras;
    tile.items.thystame = thystame;

    Ogre::SceneNode *node = tile.node;
    if (!node || node->numAttachedObjects() == 0)
        return;
    auto tileSize = node->getAttachedObject(0)->getBoundingBox().getSize();
    Ogre::Vector3 pos = node->getPosition();
    Ogre::Vector3 size = node->getAttachedObject(0)->getBoundingBox().getSize();

    for (int i = 0; i < food; i++) {
        Ogre::Entity *cubeEntity = scnMgr->createEntity("food.mesh");
        Ogre::SceneNode *foodNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        auto foodSize = cubeEntity->getBoundingBox().getSize();
        foodNode->attachObject(cubeEntity);
        foodNode->setPosition(pos.x + (rand() % 10) * size.x / 10, foodSize.y / 2 * 0.1, pos.z + (rand() % 10) * size.z / 10);
        foodNode->setScale(0.1, 0.1, 0.1);
    }
}
