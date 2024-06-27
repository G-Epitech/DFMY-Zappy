/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Level
*/

#include "Level.hpp"

PlayerLevelCommand::PlayerLevelCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void PlayerLevelCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 2)
        return;
    int id = std::stoi(args[0]);
    int level = std::stoi(args[1]);

    for (auto &player: _map.players) {
        if (player->getId() == id) {
            player->level = level;
            player->updateEntitySize(_map.tiles[player->position.x][player->position.y]->getNode());
            return;
        }
    }
}
