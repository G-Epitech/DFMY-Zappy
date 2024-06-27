/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ACommand
*/

#include "ACommand.hpp"

ACommand::ACommand(Client &client, Map &map, bool &sliderChanged)
    : _client(client), _map(map), _sliderChanged(sliderChanged) {}

ACommand::~ACommand() {}

void ACommand::setScnMgr(Ogre::SceneManager *scnMgr) {
    _scnMgr = scnMgr;
}

void ACommand::setLogs(OgreBites::TextBox *logs) {
    _logs = logs;
}

void ACommand::setSlider(OgreBites::Slider *timeSlider) {
    _timeSlider = timeSlider;
}
