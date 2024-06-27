/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Modification
*/

#include "Modification.hpp"

TimeModificationCommand::TimeModificationCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void TimeModificationCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 1 || args[0] == "0")
        return;

    _map.timeUnit = std::stoi(args[0]);
    _timeSlider->setValue(_map.timeUnit);
    _timeSliderChanged = true;
}
