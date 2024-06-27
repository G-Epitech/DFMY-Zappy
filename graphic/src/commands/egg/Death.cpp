/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Death
*/

#include "Death.hpp"

EggDeathCommand::EggDeathCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void EggDeathCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 1)
        return;
    int egg_id = std::stoi(args[0]);

    // TODO: Implement egg death animation
}
