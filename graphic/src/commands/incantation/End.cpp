/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** End
*/

#include "End.hpp"

IncantationEndCommand::IncantationEndCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void IncantationEndCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() < 3)
        return;
    int x = std::stoi(args[0]);
    int y = std::stoi(args[1]);

    for (auto &sphere: _map.incantationSpheres) {
        if (sphere.node->getPosition() == _map.tiles[x][y]->getNode()->getPosition()) {
            _scnMgr->destroySceneNode(sphere.node);
            _map.incantationSpheres.erase(
                    std::remove(_map.incantationSpheres.begin(), _map.incantationSpheres.end(), sphere),
                    _map.incantationSpheres.end());
        }
    }

    for (auto &player: _map.players) {
        if (player->position.x == x && player->position.y == y) {
            std::string command = "plv " + std::to_string(player->getId()) + "\n";
            _client.write(command);
        }
    }
}
