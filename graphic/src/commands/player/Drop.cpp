/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Drop
*/

#include <iostream>
#include "Drop.hpp"

PlayerDropCommand::PlayerDropCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void PlayerDropCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 2)
        return;
    int player_id = std::stoi(args[0]);
    std::string resource;
    if (std::stoi(args[1]) == 0)
        resource = "food";
    else
        resource = stonesNames[std::stoi(args[1]) - 1];

    for (auto &player: _map.players) {
        if (player->getId() == player_id) {
            player->removeInventoryItem(resource, 1);
            _map.tiles[player->position.x][player->position.y]->addItemEntity(resource, 1, _scnMgr);
            return;
        }
    }
}
