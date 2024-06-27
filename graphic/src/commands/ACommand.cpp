/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ACommand
*/

#include "ACommand.hpp"

ACommand::ACommand(Client &client, Map &map, bool &sliderChanged)
    : _client(client), _map(map), _timeSliderChanged(sliderChanged) {}

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

void ACommand::_addLogMessage(const std::string &message) {
    if (!_logs)
        return;
    auto previousText = _logs->getText();
    if (previousText.size() > 1000)
        previousText = previousText.substr(0, 1000);
    _logs->setText(message + "\n" + previousText);
}

void ACommand::setDropdown(OgreBites::SelectMenu *dropdown) {
    _dropdown = dropdown;
}
