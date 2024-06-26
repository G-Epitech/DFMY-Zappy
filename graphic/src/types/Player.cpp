/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#include "Player.hpp"

std::vector<std::string> playerModels = {"Barbar.mesh", "Queen.mesh", "Warden.mesh", "Colt.mesh", "Shelly.mesh", "Spike.mesh"};

Player::Player(int id, std::string team)
{
    _id = id;
    _team = team;
    level = 1;
    orientation = 0;
    position = {0, 0};
    _inventory = {};
    node = nullptr;
}

std::string Player::getTeam() const
{
    return _team;
}

int Player::getId() const
{
    return _id;
}

void Player::createEntity(Ogre::SceneManager *scnMgr, Teams &teams, Ogre::Node *tileNode)
{
    std::size_t teamIndex = teams.teamIndex(_team);

    if (teamIndex >= playerModels.size())
        teamIndex = 0;
    Ogre::Entity *cubeEntity = scnMgr->createEntity(playerModels[teamIndex]);
    node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(cubeEntity);

    updateEntitySize(tileNode);
}

void Player::updateEntitySize(Ogre::Node *tileNode) const
{
    auto *entity = dynamic_cast<Ogre::Entity *>(node->getAttachedObject(0));
    Ogre::AxisAlignedBox boundingBox = entity->getBoundingBox();
    Ogre::Vector3 size = boundingBox.getSize();
    float playerScale = static_cast<float>(level) * PLAYER_SCALE;
    auto final_orientation = static_cast<float>((orientation - 1) * 90);

    node->setPosition(tileNode->getPosition().x, 0.0f, tileNode->getPosition().z);
    node->setScale(playerScale, playerScale, playerScale);
    //node->setOrientation(Ogre::Quaternion(Ogre::Degree(final_orientation), Ogre::Vector3::UNIT_Y));
}

void Player::addInventoryItem(const std::string &item, int quantity) {
    if (_inventory.find(item) == _inventory.end())
        _inventory[item] = 0;
    _inventory[item] += quantity;
}

int Player::getItemQuantity(const std::string &item) const {
    if (_inventory.find(item) == _inventory.end())
        return 0;
    return _inventory.at(item);
}
