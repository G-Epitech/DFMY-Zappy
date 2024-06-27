/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Eject
*/

#include <iostream>
#include "Eject.hpp"

PlayerEjectCommand::PlayerEjectCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void PlayerEjectCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 1)
        return;
    int id = std::stoi(args[0]);

    // TODO: Implement player ejection
    std::cout << "Player " << id << " have been ejected or eject others?" << std::endl;
}
