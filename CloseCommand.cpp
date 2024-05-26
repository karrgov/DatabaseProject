#include "CloseCommand.h"

CloseCommand::CloseCommand(const std::string& name) : CommandInterface(name)
{

}

CloseCommand::~CloseCommand()
{

}

void CloseCommand::applyCommand(const std::string& parameters, Catalogue*& database)
{
    if(database == nullptr)
    {
        std::cerr << "Error while closing the database!" << std::endl;
        std::cout << std::endl;
        return;
    }

    delete database;
    database = nullptr;
    std::cout << "Database closed!" << std::endl;
    std::cout << std::endl;
}
