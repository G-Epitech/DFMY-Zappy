/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Start
*/

#include "Start.hpp"

IncantationStartCommand::IncantationStartCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void IncantationStartCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() < 3)
        return;
    int x = std::stoi(args[0]);
    int y = std::stoi(args[1]);
    int level = std::stoi(args[2]);

    Sphere sphere = _createIncantationSphere(_map.tiles[x][y]->getNode()->getPosition());
    _map.incantationSpheres.push_back(sphere);
}

Sphere IncantationStartCommand::_createIncantationSphere(const Ogre::Vector3 &position) {
    Sphere sphere;
    sphere.sphere = _scnMgr->createManualObject();
    sphere.node = _scnMgr->getRootSceneNode()->createChildSceneNode();
    sphere.node->attachObject(sphere.sphere);
    sphere.node->setPosition(position);

    return sphere;
}
