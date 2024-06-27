/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Broadcast
*/

#include "Broadcast.hpp"

PlayerBroadcastCommand::PlayerBroadcastCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void PlayerBroadcastCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() < 2)
        return;
    int id = std::stoi(args[0]);
    std::string message = args[1];

    for (auto &player: _map.players) {
        if (player->getId() == id) {
            if (!_map.selectedTeam.empty() && _map.selectedTeam != player->getTeam()) {
                return;
            }

            Circle circle = _createBroadcastCircle(player->node->getPosition());
            _map.broadcastCircles.push_back(circle);
            _addLogMessage("Player " + std::to_string(id) + " broadcasted: " + message);
            return;
        }
    }
}

Circle PlayerBroadcastCommand::_createBroadcastCircle(const Ogre::Vector3 &position) {
    Circle circle;
    circle.circle = _scnMgr->createManualObject();
    circle.node = _scnMgr->getRootSceneNode()->createChildSceneNode();
    circle.node->attachObject(circle.circle);
    circle.node->setPosition(position);
    circle.radius = 0;

    circle.circle->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
    for (int i = 0; i <= BROADCAST_CIRCLE_SEGMENTS; ++i) {
        float angle = Ogre::Math::TWO_PI * i / BROADCAST_CIRCLE_SEGMENTS;
        circle.circle->position(Ogre::Math::Cos(angle) * circle.radius, 0, Ogre::Math::Sin(angle) * circle.radius);
    }
    circle.circle->end();

    return circle;
}

