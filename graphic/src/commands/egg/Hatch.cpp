/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Hatch
*/

#include "Hatch.hpp"

EggHatchCommand::EggHatchCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void EggHatchCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 1)
        return;
    int egg_id = std::stoi(args[0]);

    // TODO: Implement egg hatching animation
}
