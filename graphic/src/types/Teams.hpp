/*
** EPITECH PROJECT, 2024
** Teams.hpp
** File description:
** Teams class
*/

#pragma once

#include <list>
#include <string>
#include <algorithm>

class Teams {
    public:
        Teams();
        ~Teams();

        void addTeam(const std::string& teamName);
        bool teamExists(const std::string& teamName);
        std::size_t teamIndex(const std::string& teamName);
    private:
        std::list<std::string> _teamsNames;
};
