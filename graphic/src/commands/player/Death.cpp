/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Death
*/

#include "Death.hpp"

PlayerDeathCommand::PlayerDeathCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void PlayerDeathCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 1)
        return;
    int player_id = std::stoi(args[0]);

    for (auto &player: _map.players) {
        if (player->getId() == player_id) {
            if (player->node)
                _scnMgr->destroySceneNode(player->node);
            _map.players.erase(std::remove(_map.players.begin(), _map.players.end(), player), _map.players.end());
            return;
        }
    }
}
