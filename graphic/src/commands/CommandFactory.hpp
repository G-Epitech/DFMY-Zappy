/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** CommandFactory
*/

#pragma once

#include "types/Map.hpp"
#include "client/Client.hpp"
#include "interfaces/ICommand.hpp"

class CommandFactory {
    public:

        /**
         * @brief Construct a new CommandFactory object
         * @param client Client object to send commands to the server
         * @param map Map object to update the game state
         * @param sliderChanged Boolean to check if the slider was changed
         */
        CommandFactory(Client &client, Map &map, bool &sliderChanged);

        /**
         * @brief Destroy the CommandFactory object
         */
        ~CommandFactory();


        /**
         * @brief Create a command object
         * @param commandName The type of the command
         * @return std::unique_ptr<ICommand> The command object
         */
        void commandRegister(
                const std::string& commandName,
                std::function<std::unique_ptr<ICommand>()> constructor);


        /**
         * @brief Create a Command object
         * @param commandName The name of the command
         * @return std::unique_ptr<ICommand> The command object
         */
        std::unique_ptr<ICommand> createCommand(const std::string &commandName);

    private:
        std::map<std::string, std::function<std::unique_ptr<ICommand>()>> _commands;
};
