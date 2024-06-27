/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** End
*/

#include "End.hpp"
#include <iostream>

GameEndCommand::GameEndCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void GameEndCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 1)
        return;
    std::string winner = args[0];

    std::cout << "Game ended, team " << winner << " won!" << std::endl;
}
