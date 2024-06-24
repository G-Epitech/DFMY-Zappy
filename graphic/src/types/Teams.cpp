/*
** EPITECH PROJECT, 2024
** Teams.cpp
** File description:
** Teams class
*/

#include "Teams.hpp"

Teams::Teams() {
    this->_teamsNames = {};
}

Teams::~Teams() = default;

void Teams::addTeam(const std::string& teamName) {
    if (this->teamExists(teamName))
        return;

    this->_teamsNames.push_back(teamName);
}

bool Teams::teamExists(const std::string& teamName) {
    return std::find(this->_teamsNames.begin(), this->_teamsNames.end(), teamName) != this->_teamsNames.end();
}

std::size_t Teams::teamIndex(const std::string& teamName) {
    return std::distance(this->_teamsNames.begin(), std::find(this->_teamsNames.begin(), this->_teamsNames.end(), teamName));
}