#include "PrintCommand.h"

PrintCommand::PrintCommand(const std::string& name) : CommandInterface(name)
{

}

PrintCommand::~PrintCommand()
{

}

void PrintCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while printing the table!" << std::endl;
        std::cout << std::endl;
        return;
    }

    database->printTable(parameters);
}