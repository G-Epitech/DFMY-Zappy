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
            node->setPosition(posx * size.x, 0, posy * size.z);

            Tile tile;
            tile.node = node;
            row.push_back(tile);
            posy = posy - 1;
        }
        map.tiles.push_back(row);
        posx = posx - 1;
    }
}
