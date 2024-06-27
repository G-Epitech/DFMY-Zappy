/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Connect
*/

#include "Connect.hpp"

PlayerConnectCommand::PlayerConnectCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void PlayerConnectCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 6)
        return;
    int id = std::stoi(args[0]);
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);
    int orientation = std::stoi(args[3]);
    int level = std::stoi(args[4]);
    std::string team = args[5];

    if (x < 0 || x >= _map.width || y < 0 || y >= _map.height)
        return;

    for (const auto &player: _map.players) {
        if (player->getId() == id) {
            return;
        }
    }

    auto player = std::make_shared<Player>(id, team);
    player->orientation = orientation;
    player->level = level;
    player->position = {x, y};
    player->createEntity(_scnMgr, _map.teams, _map.tiles[x][y]->getNode());
    _map.players.push_back(player);

    _client.write("pin " + std::to_string(id) + "\n");

    if (!_map.selectedTeam.empty() && _map.selectedTeam != team) {
        player->node->setVisible(false);
    }
}
