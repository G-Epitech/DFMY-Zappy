/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#include "Player.hpp"

std::vector<std::string> playerModels = {"Barbar.mesh", "Queen.mesh", "Warden.mesh", "Colt.mesh", "Shelly.mesh", "Spike.mesh"};
std::vector<float> orientationToRotation = {180, 270, 0, 90};

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
    node->setOrientation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));

    _playerModelLoad = true;
    updateEntitySize(scnMgr, teams, tileNode);

    if (!teams.teamExists(_team))
        _playerModelLoad = false;
}

void Player::updateEntitySize(Ogre::SceneManager *scnMgr, Teams &teams, Ogre::Node *tileNode)
{
    auto *entity = dynamic_cast<Ogre::Entity *>(node->getAttachedObject(0));

    std::size_t teamIndex = teams.teamIndex(_team);
    if (teamIndex >= playerModels.size())
        teamIndex = 0;
    if (!_playerModelLoad) {
        scnMgr->destroySceneNode(node);
        return this->createEntity(scnMgr, teams, tileNode);
    }

    Ogre::AxisAlignedBox boundingBox = entity->getBoundingBox();
    Ogre::Vector3 size = boundingBox.getSize();
    float playerScale = static_cast<float>(level) * PLAYER_SCALE;
    auto final_orientation = orientationToRotation[orientation - 1];

    node->setPosition(tileNode->getPosition().x, 0.0f, tileNode->getPosition().z);
    node->setScale(playerScale, playerScale, playerScale);
    node->setOrientation(Ogre::Quaternion(Ogre::Degree(final_orientation), Ogre::Vector3::UNIT_Y));
}

void Player::addInventoryItem(const std::string &item, int quantity) {
    if (_inventory.find(item) == _inventory.end())
        _inventory[item] = quantity;
    _inventory[item] += quantity;
}

void Player::removeInventoryItem(const std::string &item, int quantity) {
    if (_inventory.find(item) == _inventory.end())
        _inventory[item] = 0;
    _inventory[item] -= quantity;
}

int Player::getItemQuantity(const std::string &item) const {
    if (_inventory.find(item) == _inventory.end())
        return 0;
    return _inventory.at(item);
}
