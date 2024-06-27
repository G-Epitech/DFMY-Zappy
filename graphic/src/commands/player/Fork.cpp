/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Fork
*/

#include "Fork.hpp"

PlayerForkCommand::PlayerForkCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void PlayerForkCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 1)
        return;
    int player_id = std::stoi(args[0]);

    // TODO: Implement egg laying animation
}
