/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Size
*/

#include "Size.hpp"

std::vector<std::string> stonesNames = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

MapSizeCommand::MapSizeCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void MapSizeCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 2)
        return;

    _map.width = std::stoi(args[0]);
    _map.height = std::stoi(args[1]);
    float posx = static_cast<float>(_map.width) / 2;
    float posy;
    float rotation;
    for (int i = 0; i < _map.width; i++) {
        std::vector<std::shared_ptr<Tile>> row;
        posy = static_cast<float>(_map.width) / 2;
        for (int j = 0; j < _map.height; j++) {
            Ogre::Entity *cubeEntity = _scnMgr->createEntity("Island.mesh");
            Ogre::SceneNode *node = _scnMgr->getRootSceneNode()->createChildSceneNode();

            node->attachObject(cubeEntity);

            Ogre::AxisAlignedBox aab = cubeEntity->getBoundingBox();
            Ogre::Vector3 size = aab.getSize();

            node->setPosition(posx * size.x, (-size.y / 2.0), posy * size.z);
            rotation = static_cast<float>(std::rand()) / RAND_MAX * 360;
            node->setOrientation(Ogre::Quaternion(Ogre::Degree(rotation), Ogre::Vector3::UNIT_Y));
            node->setScale(TILE_SCALE, TILE_SCALE, TILE_SCALE);

            auto tile = std::make_shared<Tile>(node);

            for (const auto &stonesName: stonesNames) {
                tile->items[stonesName] = {};
            }
            row.push_back(tile);
            posy = posy - 1 - MAP_TILE_Y_OFFSET;
        }

        _map.tiles.push_back(row);
        posx = posx - 1 - MAP_TILE_X_OFFSET;
    }
}
