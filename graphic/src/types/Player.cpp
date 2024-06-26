/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(int id, std::string team)
{
    _id = id;
    _team = team;
    level = 1;
    orientation = 0;
    position = {0, 0};
    _inventory = {};
}

std::string Player::getTeam() const
{
    return _team;
}

int Player::getId() const
{
    return _id;
}
