/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Laid
*/

#include "Laid.hpp"

EggLaidCommand::EggLaidCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void EggLaidCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 4)
        return;
    int player_id = std::stoi(args[0]);
    int egg_id = std::stoi(args[1]);
    int x = std::stoi(args[2]);
    int y = std::stoi(args[3]);

    // TODO: Implement egg laying animation
}
