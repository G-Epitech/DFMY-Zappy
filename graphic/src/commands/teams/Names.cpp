/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Name
*/

#include "Names.hpp"

TeamsNamesCommand::TeamsNamesCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void TeamsNamesCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 1)
        return;

    for (const auto &arg: args) {
        _map.teams.addTeam(arg);
        _dropdown->addItem(arg);
    }
}
