/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Position
*/

#include "Position.hpp"

PlayerPositionCommand::PlayerPositionCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void PlayerPositionCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 4)
        return;
    int id = std::stoi(args[0]);
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);
    int orientation = std::stoi(args[3]);
    if (x < 0 || x >= _map.width || y < 0 || y >= _map.height)
        return;
    for (auto &player: _map.players) {
        if (player->getId() == id) {
            player->position.x = x;
            player->position.y = y;
            player->orientation = orientation;
            player->node->setPosition(_map.tiles[x][y]->getNode()->getPosition().x, player->node->getPosition().y,
                                      _map.tiles[x][y]->getNode()->getPosition().z);
            if (!player->node)
                player->createEntity(_scnMgr, _map.teams, _map.tiles[x][y]->getNode());
            else
                player->updateEntitySize(_scnMgr, _map.teams, _map.tiles[x][y]->getNode());
            return;
        }
    }
}
