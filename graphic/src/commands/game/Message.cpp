/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Message
*/

#include "Message.hpp"
#include <iostream>

GameMessageCommand::GameMessageCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void GameMessageCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 1)
        return;
    std::string message = args[0];

    std::cout << "Message received: " << message << std::endl;
}
