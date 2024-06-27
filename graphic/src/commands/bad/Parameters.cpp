/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Parameters
*/

#include "Parameters.hpp"
#include <iostream>

BadParametersCommand::BadParametersCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void BadParametersCommand::execute(std::string &params) {
    std::cout << "Graphic send bad parameters" << std::endl;
}
