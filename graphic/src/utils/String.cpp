/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** String
*/

#include <sstream>
#include "String.hpp"

using namespace Utils;

std::vector<std::string> StringUtils::split(const std::string &str, const char delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(str);

    while (std::getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}
