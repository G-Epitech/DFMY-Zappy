/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#include "Player.hpp"

bool operator==(const Player& lhs, const Player& rhs) {
    return lhs.id == rhs.id;
}
