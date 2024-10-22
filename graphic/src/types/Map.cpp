/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Map
*/

#include "Map.hpp"

bool operator==(const Circle &lhs, const Circle &rhs)
{
    return lhs.node == rhs.node && lhs.radius == rhs.radius && lhs.circle == rhs.circle;
}

bool operator==(const Sphere &lhs, const Sphere &rhs)
{
    return lhs.node == rhs.node;
}
