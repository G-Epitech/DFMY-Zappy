/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** String
*/

#include "String.hpp"

using namespace Utils;

std::vector<std::string> StringUtils::split(const std::string &str, const char delim)
{
    std::vector<std::string> result;
    std::string tmp = "";

    for (char c : str) {
        if (c == delim) {
            result.push_back(tmp);
            tmp = "";
        } else {
            tmp += c;
        }
    }
    result.push_back(tmp);
    return result;
}
