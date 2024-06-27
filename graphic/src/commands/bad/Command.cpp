/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Command
*/

#include "Command.hpp"
#include <iostream>

BadCommandCommand::BadCommandCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void BadCommandCommand::execute(std::string &params) {
    std::cout << "Graphic send a bad command" << std::endl;
}
