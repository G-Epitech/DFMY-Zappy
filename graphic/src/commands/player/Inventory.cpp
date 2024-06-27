/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Inventory
*/

#include "Inventory.hpp"

PlayerInventoryCommand::PlayerInventoryCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void PlayerInventoryCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 10)
        return;
    int id = std::stoi(args[0]);
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);

    if (x < 0 || x >= _map.width || y < 0 || y >= _map.height)
        return;

    for (auto &player: _map.players) {
        if (player->getId() == id) {
            player->addInventoryItem("food", std::stoi(args[3]));
            player->addInventoryItem("linemate", std::stoi(args[4]));
            player->addInventoryItem("deraumere", std::stoi(args[5]));
            player->addInventoryItem("sibur", std::stoi(args[6]));
            player->addInventoryItem("mendiane", std::stoi(args[7]));
            player->addInventoryItem("phiras", std::stoi(args[8]));
            player->addInventoryItem("thystame", std::stoi(args[9]));
            return;
        }
    }
}
