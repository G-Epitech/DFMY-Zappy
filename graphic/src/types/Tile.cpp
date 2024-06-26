/*
** EPITECH PROJECT, 2024
** Tile.cpp
** File description:
** Tile class
*/

#include "Tile.hpp"

Tile::Tile(Ogre::SceneNode *node) {
    _node = node;
}

Ogre::SceneNode *Tile::getNode() const {
    return _node;
}

void Tile::addItemEntity(const std::string &name, int quantity, Ogre::SceneManager *scnMgr) {
    if (!_node || _node->numAttachedObjects() == 0)
        return;
    auto tileSize = _node->getAttachedObject(0)->getBoundingBox().getSize();
    Ogre::Vector3 pos = _node->getPosition();
    Ogre::Vector3 size = _node->getAttachedObject(0)->getBoundingBox().getSize();

    for (int i = 0; i < quantity; i++) {
        Ogre::Entity *cubeEntity = scnMgr->createEntity(name + ".mesh");
        Ogre::SceneNode *itemNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        auto itemSize = cubeEntity->getBoundingBox().getSize();

        itemNode->attachObject(cubeEntity);

        float randX = pos.x + static_cast<float>(std::rand()) / RAND_MAX * tileSize.x - tileSize.x / 2.0f;
        float randZ = pos.z + static_cast<float>(std::rand()) / RAND_MAX * tileSize.z - tileSize.z / 2.0f;
        float itemY = itemSize.y / 2.0f * 0.1;

        itemNode->setPosition(randX, itemY, randZ);
        itemNode->setScale(0.1f, 0.1f, 0.1f);
        items[name].push_back(itemNode);
    }
}

void Tile::removeItemEntity(const std::string &name, int quantity, Ogre::SceneManager *scnMgr) {
    for (int i = 0; i < quantity; i++) {
        if (items[name].empty())
            return;
        Ogre::SceneNode *node = items[name].back();
        items[name].pop_back();
        scnMgr->destroySceneNode(node);
    }
}
