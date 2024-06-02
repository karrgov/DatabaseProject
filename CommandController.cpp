/**
 * @file CommandController.cpp
 * @author Krasimir
 * @brief This class represents a list of all available commands in the program and is responsible for parametrizing the direct user input from the console
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "CommandController.h"

/**
 * @brief Construct a new Command Controller:: Command Controller object
 * 
 * @param commands 
 */
CommandController::CommandController(const std::vector<CommandInterface*>& commands) : allCommands(commands)
{

}

/**
 * @brief Destroy the Command Controller:: Command Controller object
 * 
 */
CommandController::~CommandController()
{
    for(CommandInterface* element : this->allCommands)
    {
        delete element;
    }
    this->allCommands.clear();
}

/**
 * @brief Waits and processes a command entered by the user, applying it to the provided database and returns false if the command is "exit", signaling the program should terminate or returns true, indicating the command processing loop should continue
 * 
 * @param database 
 * @return true 
 * @return false 
 */
bool CommandController::isCommandAvailable(Catalogue*& database)
{
    std::cout << "Waiting for command:" << std::endl;
    std::cout << std::endl;

    std::string line;
    std::getline(std::cin, line);

    if(line.size() == 0)
    {
        return true;
    }

    std::string currentCommand;
    std::string commandParameters;

    int i = 0;
    for(; i < line.size(); i++)
    {
        if(line[i] == ' ')
        {
            i++;
            break;
        }

        currentCommand = currentCommand + line[i];
    }

    if(currentCommand.size() == 0)
    {
        return true;
    }

    if(currentCommand == "exit")
    {
        std::cout << "Goodbye!" << std::endl;
        return false;
    }

    for(; i < line.size(); i++)
    {
        commandParameters = commandParameters + line[i];
    }

    bool isAvailable = false;

    for(CommandInterface* element : this->allCommands)
    {
        if(element->getCommandName() == currentCommand)
        {
            element->applyCommand(commandParameters, database);
            isAvailable = true;
            break;
        }
    }

    if(isAvailable == false)
    {
        std::cerr << "Invalid command!" << std::endl;
        std::cout << std::endl;
    }
    return true;

}