#include "CommandController.h"

CommandController::CommandController(const std::vector<CommandInterface*>& commands) : allCommands(commands)
{

}

CommandController::~CommandController()
{
    for(CommandInterface* element : this->allCommands)
    {
        delete element;
    }
    this->allCommands.clear();
}

bool CommandController::isCommandAvailable(Catalogue*& database)
{
    std::cout << "Waiting for command:" << std::endl;

    std::string line;
    std::getline(std::cin, line);

    if(line.size() == 0)
    {
        return true;
    }

    std::string currentCommand;
    std::string commandParameters;

    int i = 0;
    for(i; i < line.size(); i++)
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

    for(i; i < line.size(); i++)
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
    }
    return true;

}