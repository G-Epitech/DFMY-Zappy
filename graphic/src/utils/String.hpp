/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** string
*/

#pragma once

#include <vector>
#include <string>

namespace Utils {

    /**
     * @brief A class to manipulate strings
     */
    class StringUtils {
    public:

        /**
         * @brief Split a string into a vector of strings
         * @param str The string to split
         * @param delim The delimiter
         * @return A vector of strings
         */
        static std::vector<std::string> split(const std::string &str, const char delim);
    };

}
